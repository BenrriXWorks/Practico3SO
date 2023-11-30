// Version 1.0

#include "robin_hood.h"
#include <string>
#include <getopt.h>

class ArgumentsLoader
{
private:
    robin_hood::unordered_flat_map<char,std::string> args;
    static ArgumentsLoader* instance;
    ArgumentsLoader(){};
public:
    bool loadArgs(int argc, char** argv, const char* arguments, std::string obligatoryArgs);
    static ArgumentsLoader* getInstance();
    inline std::string& operator[](char c) {return args.at(c);};
    bool checkArgs(const std::string arguments);
};