#include "include/DirCircle.h"

int main (int argc, char** argv){
    
    if(argc != 2){
        printf("Debes ingresar la ruta del archivo de directorio .dre\n");
        return EXIT_FAILURE;
    }

    std::string path = argv[1];

    DirCircle* dirCircle = DirCircle::fromFile(path, "dre");

    if(dirCircle == nullptr){
        fputs_unlocked("Hubo un error al leer el archivo .dre\n", stdout);
        return EXIT_FAILURE;
    }
    //Crear los archivos y carpetas

    dirCircle-> createDir();
    delete dirCircle;

    fputs_unlocked("Se ha concretado la creacion de archivos y directorios\n", stdout);
    return EXIT_SUCCESS;
}