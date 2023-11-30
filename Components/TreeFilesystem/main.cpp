#include "include/DirTree.h"

int main(int argc, char** argv){

    // Leer los argumentos
    if (argc != 2){
        printf("Debes ingresar la ruta del archivo de directorio .dit\n");
        return EXIT_FAILURE;
    }
    std::string path = argv[1];

    // Leer el JSON .dit
    DirTree* dirTree = DirTree::fromFile(path, "dit");
    if (dirTree == nullptr){
        fputs_unlocked("Hubo un error al leer el archivo .dit\n", stdout);
        return EXIT_FAILURE;
    }

    // Crear los archivos y carpetas
    dirTree->createDir();
    fputs_unlocked("Creacion finalizada\n", stdout);

    // Ejecutar el tree
    if (!dirTree->getjs().contains("dirBase")) return EXIT_FAILURE;
    fputs_unlocked("Ejecutando tree en dirBase:\n\n", stdout);
    std::string command = std::string("tree -p ") + (path[0] == '/' ? "" : "./") + (std::string) dirTree->getjs()["dirBase"];
    if (system(command.c_str()))
        fputs_unlocked("Hubo un error al imprimir la respuesta, revision manual requerida\n", stdout);
    
    return EXIT_SUCCESS;

}
