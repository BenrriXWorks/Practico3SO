#include "../../include/FileStack.h"

FileReader* FileStack::next() {
    //std::lock_guard<std::mutex> lock(dequeueMutex);  // Bloquea el acceso a cola multihilos

    if (size > 0) 
        return cola.at(--size); // Decrementa size antes de acceder al elemento
    else 
        throw std::runtime_error("La cola está vacía");
    
}
 

FileStack::FileStack(std::vector<std::string> listOfPaths, std::string extension){
    try{
        size = listOfPaths.size();
        for (std::string s : listOfPaths){
            // Se separa el archivo encontrado de la extension
            size_t dotPos = s.find_last_of('.');
            if (dotPos == std::string::npos) // Si no tiene extension
                printf("El archivo {%s} no tiene una extension valida, saltando\n",s.c_str()),
                --size;
            else if (s.substr(dotPos+1) != extension) // Si no es de la extension
                --size;
            else {
                FileReader *fr = new FileReader();
                if (!fr->open(s)) // Si el archivo es inaccessible
                    printf("El archivo en {%s} no ha podido ser leido. Saltando.\n",s.c_str()),
                    --size;
                else
                    cola.push_back(fr);   
            }           
        }
    }
    catch(...){
        printf("FileStack: Error de inicializacion\n");
        exit(EXIT_FAILURE);
    }
    
};
