// Version 1.1

#include "robin_hood.h"
#include <string>
#include <getopt.h>
#pragma once

class ArgumentsLoader
{
private:
    robin_hood::unordered_flat_map<char,std::string> args;
    static ArgumentsLoader* instance;
    ArgumentsLoader(){};
public:
    bool loadArgs(int argc, char** argv, const char* arguments, std::string obligatoryArgs);
    static ArgumentsLoader* getInstance();
    inline std::string operator[](char c) {try{return args.at(c);}catch(...){return "";};};
    bool checkArgs(const std::string arguments);
    inline robin_hood::unordered_flat_map<char,std::string> getAllArgs() {return args;};
};