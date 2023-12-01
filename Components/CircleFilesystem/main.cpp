#include "include/DirCircle.h"

int main (int argc, char** argv){
    //Leer los argumentos
    if(argc != 4){
        printf("Debes ingresar la ruta del archivo de directorio .dre y el maximo de directorios y archivos\n");
        return EXIT_FAILURE;
    }

    std::string path = argv[1];
    int N = atoi(argv[2]);
    int R = atoi(argv[3]);

    //Se crea el objeto dirCircle a partir del archivo.dre
    DirCircle* dirCircle = DirCircle::fromFile(path, "dre",N,R);
    
    //si no se logro crear bien lanza mensaje de error y se sale
    if(dirCircle == nullptr){
        fputs_unlocked("Hubo un error al leer el archivo .dre\n", stdout);
        
        return EXIT_FAILURE;
    }
    
    //aqui se crean las carpetas 
    dirCircle-> createDir();
    fputs_unlocked("Se ha concretado la creacion de archivos y directorios\n", stdout);
    
    //imprimir tree solo si se creo bien el directorio base
    fputs_unlocked("Ejecutando tree en dirBase:\n\n", stdout);
    std::string command = std::string("tree ") + (path[0] == '/' ? "" : "./") + (std::string) dirCircle->getDirbase();
    if (system(command.c_str()))
        fputs_unlocked("Hubo un error al imprimir la respuesta, revision manual requerida\n", stdout);
    
    delete dirCircle;
    return EXIT_SUCCESS;
}