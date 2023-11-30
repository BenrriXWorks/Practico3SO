#include "../../include/EnvLoader.h"
using namespace std;

EnvLoader* EnvLoader::instance = nullptr;
robin_hood::unordered_flat_map<std::string, std::string> EnvLoader::env = robin_hood::unordered_flat_map<std::string, std::string>();

EnvLoader* EnvLoader::getInstance(){
    if (instance == nullptr)
        instance = new EnvLoader();
    return instance;
}

bool EnvLoader::loadEnv(std::string path){
    FileReader fr;
    if (!fr.open(path)){
        printf("EnvLoader: No se pudo leer el archivo de env\n");
        return false;
    }
    for (const string& line : split(fr.read(),'\n')){
        if (!line.empty()){
            auto p = split1(line,'=');
            if (!p.first.empty() && !p.second.empty()){
                env[p.first] = getenv(p.first.c_str()) == nullptr ? p.second : string(getenv(p.first.c_str()));
                setenv(p.first.c_str(),p.second.c_str(),1);
            }
        }
    };
    return true;
}