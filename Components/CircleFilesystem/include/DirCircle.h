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
    std::string dirbase;
    std::map <std::string, std::vector<std::string>> dirs;
    std::map <std::string, std::string> rutas;
    bool process(std::string path, int N , int R);

    void createSubdirs();
    void createFiles();

public:
    std::string getDirbase(){return dirbase;}
    static DirCircle* fromFile(std::string path, std::string extension, int N, int R);
    void createDir();

};