#include "include/FileStack.h"
#include "include/ThreadProcessor.h"
#include <filesystem>
#include <vector>
#include <unordered_set>
#include <csignal>
#include <chrono>
#include <regex>
using namespace std;

class Main{

private:

    // Validar que el nombre sea {file}[0-9]+
    static bool esNombreArchivoValido(const string& nombreArchivo, const string& ext) {
        regex patron(string("^file\\d+\\.") + ext + "$");
        return regex_match(nombreArchivo, patron);
    }

    // Devuelve el nombre de todos los archivos en un directorio con cierta extension.
    static pair<vector<string>,bool> archivosEnDirectorio(const filesystem::path& directorio, const string& extension) {
        vector<string> archivos;
        try {
            if (filesystem::exists(directorio) && filesystem::is_directory(directorio)) {
                for (const auto& archivo : filesystem::directory_iterator(directorio)) 
                    if (archivo.is_regular_file()) {
                        if (extension.empty()) 
                            archivos.push_back(archivo.path().string());
                        else 
                            // Comparar la extensión del archivo con la extensión deseada (sin el punto)
                            if (esNombreArchivoValido(archivo.path().filename().string(),extension)){
                                if (filesystem::file_size(archivo.path()) > 1'000'000)
                                    archivos.push_back(archivo.path().string());
                                else printf("Main (archivosEnDirectorio): Peso de %s menor a 1MB, saltando\n",archivo.path().string().c_str());
                            }
                    }
            } else {
                cerr << "Main (archivosEnDirectorio): El directorio no existe o no es válido: " << directorio << endl;
                return make_pair(vector<string>(),false);
            }
        } 
        catch (const filesystem::filesystem_error& ex) {
            cerr << "Error al abrir el directorio: " << ex.what() << endl;
            return make_pair(vector<string>(),false);
        }
        return make_pair(archivos,true);
    }


    // Concatena Processed/ + route a un vector con nombres de archivos.
    static vector<string> processRoute(vector<string> routes){
        vector<string> processed_nombres;
        for (string r : routes)
            processed_nombres.push_back(string("Processed/") + r.substr(r.find_last_of("\\/") + 1));
        return processed_nombres;
    }

    

public:

    static bool main(string extension, string path_files_in, string path_files_out, string threads){
        // Se normaliza el texto y se guarda en la carpeta Processed.
        auto t1 = chrono::high_resolution_clock::now();
        fputs("Main: Preprocesando archivos...\n", stdout);
        string INDEXER_PATH = getenv("INDEXER_PATH") == nullptr ? "" : getenv("INDEXER_PATH");
        string call = "python3 " + INDEXER_PATH + "/normalizaTexto.py";


        if (archivosEnDirectorio(path_files_in, extension).second == false) {
            printf("Main: No se pudieron leer los archivos del directorio {%s}\n", path_files_in.c_str());
            return false;
        }


        vector<string> archivosDirectorio = archivosEnDirectorio(path_files_in, extension).first;
        if (archivosDirectorio.size() < 20 && 
            (getenv("AT_LEAST_20_FILES_INDEX") == nullptr || string(getenv("AT_LEAST_20_FILES_INDEX"))  == string("1"))){
            printf("Main: Deben haber al menos 20 archivos validos en la carpeta!\n");
            return false;
        }


        for (string s : archivosDirectorio) {
            call += " \"" + s + "\"";
        }
        if (system(call.c_str()) != 0) {
            printf("Main: No se pudieron normalizar los archivos\n");
            return false;
        }
        auto t2 = chrono::high_resolution_clock::now();
        printf("Main: Preprocesamiento completado en %ld [ms]\n", (chrono::duration_cast<chrono::milliseconds>(t2-t1)).count());
        
        // Se abren los archivos simultaneamente en una cola.
        FileStack fileStack(processRoute(archivosDirectorio), extension);
        // Se revisan casos de borde
        if (path_files_in == path_files_out)
            {printf("Main: La carpeta de entrada no puede ser la de salida\n"); return false;}
        if (threads.find_first_not_of("0123456789") != string::npos)
            {printf("Main: La cantidad de threads contiene caracteres invalidos\n");return false;}
        int nthreads = stoi(threads);
        if (nthreads > 10) {
            fputs("Main: Se han limitado los threads a 10\n",stdout);
            nthreads = 10;
        }
        if (nthreads == 0) {
            fputs("Main: 0 threads designados, usando 1 para la ejecucion\n",stdout);
            nthreads = 1;
        }

        // Se inicia el objeto procesador, y luego se ejecutan los threads.
        ThreadProcessor tp(fileStack, nthreads, path_files_out);
        fputs("Main: Iniciando threads:\n",stdout);
        t1 = chrono::high_resolution_clock::now();
        if (!tp.begin()){
            fputs("Main: Error de ejecucion de threads\n",stdout);
            return false;
        }
        t2 = chrono::high_resolution_clock::now();
        printf("Los threads han terminado en %ld [ms]\n",(chrono::duration_cast<chrono::milliseconds>(t2-t1)).count());
        
        if (system("rm -r Processed") == 0)
            printf("Main: Cache de archivos procesados limpiado!\n");
        
        return true;
    };

};

int main(int argc, char** argv){

    auto ti = chrono::high_resolution_clock::now();

    if (argc != 5) 
        return (
            printf("La llamada de este programa debe ser:\n./main EXTENTION, PATH_FILES_IN, PATH_FILES_OUT, AMOUNT_THREADS.\n verifica si falta uno o mas y vuelve a intentarlo.\n"),
            EXIT_FAILURE
        );
    string extension = string(argv[1]), path_files_in = string(argv[2]), path_files_out = string(argv[3]), threads = string(argv[4]);
    
    // Si no se inicio correctamente, retornar fallo para que lo sepa el proceso padre
    if (!Main::main(extension, path_files_in, path_files_out, threads)) return EXIT_FAILURE;

    auto tf = chrono::high_resolution_clock::now();
    printf("Tiempo total de ejecucion de proceso PID=%d: %lu [ms]\n", getpid(), chrono::duration_cast<chrono::milliseconds>(tf-ti).count());
    return EXIT_SUCCESS;
}
