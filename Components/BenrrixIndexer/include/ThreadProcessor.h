#include "FileStack.h"
#include "Functions.h"
#include "FileWriter.h"
#include <thread>
#include <iostream>
#include <unordered_map>
#include <unistd.h>
#include <bitset>
#include "robin_hood.h"

#pragma once

class ThreadProcessor
{
private:
    std::vector<std::thread> threads;
    void execute(uint8_t threadId, const std::string& path_out); // Ejecuta la funcion requerida
    uint8_t nThreads;
    FileStack *stack;
    std::string path_out;
    unsigned long threadsFinished = 0;
public:
    // Instancia el procesador de threads
    ThreadProcessor(FileStack &stack, uint8_t nThreads, std::string path_out);
    // Comienza la ejecucion de los threads
    bool begin();

};