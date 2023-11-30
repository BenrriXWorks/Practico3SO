// Version 1.1

#include "../../include/ArgumentsLoader.h"

ArgumentsLoader* ArgumentsLoader::instance = nullptr;

ArgumentsLoader* ArgumentsLoader::getInstance(){
    if (instance == nullptr)
        instance = new ArgumentsLoader();
    return instance;
}

bool ArgumentsLoader::loadArgs(int argc, char** argv, const char* arguments, std::string obligatoryArgs){
    int option;
    while ((option = getopt(argc, argv, arguments)) != -1)
        if (option != '?')
            args[option] = optarg != nullptr ? std::string(optarg) : "";
        else return false;
    return checkArgs(obligatoryArgs);
}

bool ArgumentsLoader::checkArgs(const std::string arguments){
    for (const char& c : arguments) 
        try{
            if ((*this)[c].empty()) throw std::runtime_error("Argumento invalido ingresado\n");
        }catch(...){
            printf("ArgumentsLoader: Falta el argumento requerido %c\n",c);
            return false;
        }
    
    return true;
}