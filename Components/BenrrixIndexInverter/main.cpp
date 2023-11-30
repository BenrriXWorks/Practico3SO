#include <string>
#include <cstdio>
#include <map>
#include <thread>
#include <unistd.h>
#include <chrono>
#include "include/FileStack.h"
#include "include/Functions.h"
#include "include/FileWriter.h"
//#include <unordered_map>
#include "robin_hood.h"

using namespace std;

// Estructura para almacenar la salida
robin_hood::unordered_map<string, multimap<int, string, greater<int>>> words;
mutex wordsMutex; // Sincroniza words

void mapWords(FileStack& fs);

int main(int argc, char** argv) {
    auto t1 = chrono::high_resolution_clock::now();

    // Leer los argumentos
    if (argc != 3) {
        fputs("Main: El proceso debe llamarse como ./main \"/ruta/archivo/index.idx\" \"/ruta/archivos/procesados\"\n", stdout);
        fputs("Main: Revisa si faltan argumentos y vuelve a intentarlo.\n", stdout);
        return EXIT_FAILURE;
    }
    string rutaIndex = (string)(argv[1] == nullptr ? "" : argv[1]);
    string rutaArchivos = (string)(argv[2] == nullptr ? "" : argv[2]);

    if (rutaIndex != "" && rutaIndex.substr(rutaIndex.size()-4) != ".idx"){
        printf("Main: El archivo de salida {%s} tiene que tener la extension .idx\n",rutaIndex.c_str());
        return EXIT_FAILURE; 
    }


    FileStack fs = FileStack::fromDirectory(rutaArchivos, "*");
    if (fs.getSize() == 0) return (fputs("No hay archivos para procesar.\n", stdout), EXIT_FAILURE);

    // Agregar las palabras al diccionario
    int maxThreads = min((unsigned int)fs.getSize(), thread::hardware_concurrency());
    vector<thread> threads(maxThreads);
    for (int i = 0; i < maxThreads; i++)
        threads.at(i) = thread(mapWords, ref(fs));
    for (int i = 0; i < maxThreads; i++)
        threads.at(i).join();


    // Agregar el map de multimap al archivo de salida.
    FileWriter fw;
    fw.open(rutaIndex);
    for (const auto& wordAndFiles : words) { // Por cada 
        fw << wordAndFiles.first << ":";
        size_t i = 0;
        for (const auto& elemMap : wordAndFiles.second) 
            fw << "(" << elemMap.second << "," << elemMap.first << ")" << (++i < wordAndFiles.second.size() ? ";" : "\n");
    }
    fw.close();
    auto t2 = chrono::high_resolution_clock::now();
    printf("El proceso pid=%d genero el archivo=%s\n", getpid(), rutaIndex.c_str());
    printf("Tiempo de ejecucion: %lu [ms]\n", chrono::duration_cast<chrono::milliseconds>(t2 - t1).count());

    return EXIT_SUCCESS;
}

void mapWords(FileStack& fs) {
    robin_hood::unordered_map<string, multimap<int, string, greater<int>>> localWords;

    while (!fs.empty()) {
        FileReader* fr = fs.next();
        auto file = fr->read();
        for (const auto& line : split(file, '\n')) {
            pair<string, string> par = split1(line, ',');
            localWords[par.first].emplace(stoi(par.second), fr->getFilename());
        }
    }

    // Bloquear el acceso a words y fusionar los resultados locales.
    lock_guard<mutex> lock(wordsMutex);
    for (const auto& entry : localWords) {
        for (const auto& wordAndFiles : entry.second) {
            words[entry.first].emplace(wordAndFiles);
        }
    }
}