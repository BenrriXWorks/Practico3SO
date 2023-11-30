#include "../../include/FunctionPackage_1.h"
using namespace std;

void createIndexFolder(){

    fputs("FunPac_1:\n",stdout);

    EnvLoader env = *EnvLoader::getInstance();
    try{
        // Se llama al proceso externo con las variables de entorno correspondientes.
        string call = (env["AT_LEAST_20_FILES_INDEX"] != "" ? "AT_LEAST_20_FILES_INDEX=" + env["AT_LEAST_20_FILES_INDEX"] + " " : "") + env["INDEXER_PATH"] + "/main ";
        if (call == "") return (void) (printf("createIndexFolder: No se ha encontrado el archivo indexador\n"));
        call += env["EXTENTION"] + " " + env["PATH_FILES_IN"] + " " + env["PATH_FILES_OUT"] + " " + env["AMOUNT_THREADS"];
        printf("Ejecutando: %s\n",call.c_str());
        if (system(call.c_str()) == 0) setenv("INDEX_CREATED?","1",1); // Se coloca en el entorno si fue un exito
    } catch(...) {
        printf("Falta alguna de las variables de entorno necesarias: INDEXER_PATH EXTENTION, PATH_FILES_IN, PATH_FILES_OUT o AMOUT_THREADS");
    }
}

void invertIndexFolder(){
    
    fputs("FunPac_1:\n",stdout);

    if (getenv("INDEX_CREATED?") == nullptr) { // Se lee si la opcion createIndexFolder marco un exito
        printf("invertIndexFolder: Debes ejecutar correctamente primero la opcion createIndexFolder\n");
        return;
    }
    try {
        // Se llama al proceso externo con las variables de entorno. Revisando si existen.
        EnvLoader env = *EnvLoader::getInstance();
        string call = env["INVERTED_INDEXER_PATH"] + "/main " + env["INVERTED_INDEX_FILE"] + " " + env["PATH_FILES_OUT"];
        printf("Ejecutando: %s\n",call.c_str());
        if (system(call.c_str()) != 0){
            printf("invertIndexFolder: Hubo un error al ejecutar el proceso main en %s\n",env["INVERTED_INDEX_PATH"].c_str());
        }
        setenv("INVERTED_INDEX_EXECUTED?","1",1);
    } catch (...) {
        printf("invertIndexFolder: Hubo un error al llamar al proceso designado.\n");
        printf("Verifica las variables de entorno: PATH_FILES_OUT & INVERTED_INDEX_FILE");
    }
   
}

void contarPalabras(){

    fputs("FuncPac_1:\n",stdout);
    ArgumentsLoader args = *ArgumentsLoader::getInstance();
    EnvLoader env = *EnvLoader::getInstance();
    if (args['i'] == "" || args['o'] == ""){
        printf("contarPalabras: Debes definir los argumentos -i y -o\n");
        return;
    }
    if (args['o'].substr(args['o'].size()-4) != ".txt"){
        printf("contarPalabras: Por seguridad, la extension de salida debe ser .txt\n");
        return;
    }
    if (args['o'] == args['i']){
        printf("contarPalabras: La ruta de entrada no puede ser la misma que la de salida (-i,-o)\n");
        return;
    }

    string rutaSalida;
    if (args['o'].find_last_of("/\\") != string::npos)
        rutaSalida = args['o'].substr(0,args['o'].find_last_of("/\\"));
    else
        rutaSalida = string(".");
    // Crea una carpeta temporal y copia el archivo -i ahi, ejecuta el indexer en esa carpeta y la guarda en al carpeta de salida, luego se renombra
    string call = "mkdir .temp && cp " + args['i'] + " .temp/file001.txt > /dev/null 2>&1 && AT_LEAST_20_FILES_INDEX=0 " + env["INDEXER_PATH"]
        + "/main txt .temp " + rutaSalida + " 1 > /dev/null 2>&1 && mv " + rutaSalida + "/file001.txt " + args['o'] + " > /dev/null 2>&1";
    printf("Ejecutando: %s\n",call.c_str());
    if (system(call.c_str()))
        printf("contarPalabras:\nNo se pudo contar las palabras del archivo {%s}\n",args['i'].c_str());
    else
        printf("contarPalabras: Se guardo el archivo de salida en {%s}!\n",args['o'].c_str());
    if (system("rm -rf .temp") != 0){
        printf("contarPalabras: No se ha podido eliminar la carpeta temporal\n");
    }
}