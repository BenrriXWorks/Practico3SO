// Version 1.1

#include "robin_hood.h"
#include <string>
#include "FileReader.h"
#include "Functions.h"
#pragma once

class EnvLoader
{
private:
    static robin_hood::unordered_flat_map<std::string, std::string> env;
    static EnvLoader* instance;
    EnvLoader(){};
public:
    static EnvLoader* getInstance();
    bool loadEnv(std::string path);
    std::string operator[] (std::string s) {try {return env.at(s);}catch(...){return "";}}
};