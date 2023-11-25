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
    bool process(std::string path);

    void createSubdirs();
    void createFiles();

public:
    static DirCircle* fromFile(std::string path, std::string extension);
    void createDir();
     
};