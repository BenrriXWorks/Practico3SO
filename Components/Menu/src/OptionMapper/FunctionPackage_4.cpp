#include "../../include/FunctionPackage_4.h"
//llamarBuscador

void llamarBuscador(){

    fputs_unlocked("FunPac_4:\n",stdout);
    EnvLoader env = *EnvLoader::getInstance();

    if (getenv("INVERTED_INDEX_EXECUTED?") == nullptr){
        printf("llamarBuscador: Primero debes ejecutar correctamente\n la funcion de inversion de indice.\n");
        return;
    }

    if (env["TOPK"] == ""){
        fputs_unlocked("llamarBuscador: No se encontro la variable de entorno TOPK\n",stdout);
        return;
    }
    if (env["INVERTED_INDEX_FILE"] == ""){
        fputs_unlocked("llamarBuscador: No se encontro la variable de entorno INVERTED_INDEX_FILE\n",stdout);
        return;
    }

    std::string call ="./Components/BenrrixInvertedSearcher/main " + env["INVERTED_INDEX_FILE"]
     + " " + env["TOPK"];

    printf("Ejecutando: %s\n",call.c_str());
    if (system(call.c_str()) != 0){
        fputs_unlocked("llamarBuscador: Hubo un error al ejecutar el buscador\n",stdout);
        return;
    }
    setenv("RESTART_MENU?","1",1);
    
}