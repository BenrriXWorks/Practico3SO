#include "FileReader.h"
#include "vector"
#include <mutex>

#pragma once

class FileStack
{
private:
    std::vector<FileReader*> cola;
    size_t size=0;
    //std::mutex dequeueMutex;
public:
    FileReader* next(); // Se pasa el siguiente reader abierto.
    FileStack(std::vector<std::string> listOfPaths, std::string extension);
    inline bool empty() {return size==0;};
    inline bool lastFileClosed() {return !cola.front()->isOpen();};

};