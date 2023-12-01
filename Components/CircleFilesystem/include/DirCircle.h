#include <string>
#include <vector>
#include <map>
#include "Functions.h"
#include "FileReader.h"
#include "FileWriter.h"
#include <sys/stat.h>
#include <unistd.h> 


class DirCircle
{
private:
    //nombre del directorio base
    std::string dirbase;
    //lista de directorios y sus respectivos archivos
    std::map <std::string, std::vector<std::string>> dirs;
    //nombres de los directorios y sus respectivas rutas dentro de dirbase
    std::map <std::string, std::string> rutas;

    //Construye los directorios de dirs en dirbase y sus archivos
    bool process(std::string path, int N , int R);

    //Crea los subdidrectorios
    void createSubdirs();
    //Crea los archivos
    void createFiles();

public:
    //retorna el nombre del directorio base
    std::string getDirbase(){return dirbase;}
    //Crea el DirCircle a partir de un archivo
    static DirCircle* fromFile(std::string path, std::string extension, int N, int R);
    //Crea los directorios basado en lista circular
    void createDir();

};