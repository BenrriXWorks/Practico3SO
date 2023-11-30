#include "include/DirCircle.h"

int main (int argc, char** argv){

    if(argc != 4){
        printf("Debes ingresar la ruta del archivo de directorio .dre y el maximo de directorios y archivos\n");
        return EXIT_FAILURE;
    }

    std::string path = argv[1];
    int N = atoi(argv[2]);
    int R = atoi(argv[3]);

    DirCircle* dirCircle = DirCircle::fromFile(path, "dre",N,R);

    if(dirCircle == nullptr){
        fputs_unlocked("Hubo un error al leer el archivo .dre\n", stdout);
        return EXIT_FAILURE;
    }
    //Crear los archivos y carpetas

    dirCircle-> createDir();
    fputs_unlocked("Se ha concretado la creacion de archivos y directorios\n", stdout);
    
    
    fputs_unlocked("Ejecutando tree en dirBase:\n\n", stdout);
    std::string command = std::string("tree ") + (path[0] == '/' ? "" : "./") + (std::string) dirCircle->getDirbase();
    if (system(command.c_str()))
        fputs_unlocked("Hubo un error al imprimir la respuesta, revision manual requerida\n", stdout);
    
    delete dirCircle;
    return EXIT_SUCCESS;
}