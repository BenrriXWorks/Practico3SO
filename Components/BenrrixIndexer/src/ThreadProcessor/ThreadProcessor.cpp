#include "../../include/ThreadProcessor.h"

using namespace std;

ThreadProcessor::ThreadProcessor(FileStack &stack, uint8_t nThreads, std::string path_out) : 
    nThreads(nThreads), stack((&stack)), path_out(path_out) {
        // Se inicializan las variables y se limitan los threads.
        uint8_t maxThreads = thread::hardware_concurrency();
        if (nThreads > maxThreads){
            printf("Se asignaron más threads de los soportados por hardware, asignando %u en su lugar\n", maxThreads);
            nThreads = maxThreads;
        }
    };

void ThreadProcessor::execute(uint8_t threadId, const string& path_out) {

    while (!stack->empty()){

        FileReader* fr = stack->next(); // Se accede a un lector abierto
        robin_hood::unordered_map<string, int> words; // Estructura de almacenamiento de palabras.

        string consoleOutput = 
            string("proceso pid=") + to_string(getpid()) +
            " - archivo procesado " + fr->getFullRoute() + " por el thread "
            + to_string(threadId) + "\n";
        fputs(consoleOutput.c_str(), stdout);

        // Por cada línea, se separa en ' ' y se agrega +1 al map en "palabra"
        for (string const& line : split(fr->read(), '\n'))
            if (!line.empty())
                for (string const& word : split(line,' '))
                    if (!strip(word).empty())
                        words[word]++;
                
        // Se escribe en un archivo de salida.
        FileWriter filewriter;
        if (!filewriter.open(path_out + string("/") + fr->getFilename()))
            printf("ThreadProcessor (execute): No se pudo escribir en el archivo en {%s}", fr->getFullRoute().c_str());
        for (const auto& p : words)
            filewriter << p.first + "," + to_string(p.second) + "\n";
        filewriter.close();
    }
}

bool ThreadProcessor::begin() {

    if (stack->empty())
        return (printf("ThreadProcessor: No hay archivos para procesar.\n(Recuerda que los archivos deben llamarse file([0-9]+).(EXTENSION)\n Por ejemplo file001.txt)\n"), true);
    // Se crean threads con un lambda que llama a la función execute de esta clase.
    for (uint8_t i = 0; i < nThreads; i++) 
        threads.emplace_back([=]() { this->execute(i, path_out); });

    for (std::thread& t : threads) 
        t.join();

    return true;
}