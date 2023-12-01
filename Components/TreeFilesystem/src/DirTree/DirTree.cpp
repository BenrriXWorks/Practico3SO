#include "../../include/DirTree.h"

std::map<std::string, char> DirTree::permissionsMap {
    {"lectura",'r'},
    {"escritura",'w'}
};

DirTree* DirTree::fromFile(std::string route, std::string extension){

    // Validar la extensión
    std::string filename = route.substr(route.find_last_of("\\/") + 1); // +1 para obtener el nombre de archivo sin la barra
    std::string fileExtension = filename.substr(filename.find_last_of('.') + 1);

    if (fileExtension != extension) {
        printf("Extensión del archivo indicado es inválida\n");
        return nullptr;
    }

    // Leer el archivo
    FileReader fr;
    if (!fr.open(route)) return nullptr;

    // Crear el contenedor
    try {
        DirTree* dirTree = new DirTree();
        dirTree->setjs(nlohmann::json::parse(fr.read()));
        return dirTree;
    }
    catch(std::exception &e){
        fprintf(stderr, "El archivo .dit no tiene el formato correcto.\n");
        fprintf(stderr, "Error especifico: %s.\n", e.what());
        return nullptr;
    }
}

// Funcion auxiliar recursiva para crear los objetos
void makeObjects(std::string parentDir, const nlohmann::json& object) {

    // Revisar que esten los atributos generales
    if (!object.contains("tipo") || !object.contains("nombre")){
        printf("Objeto invalido saltado: %s, le falta nombre o tipo\n", object.dump().c_str());
        return;
    }

    std::string name = object["nombre"];
    std::string fullRoute = parentDir + "/" + name;

    // Si el objeto es un archivo, crearlo y otorgarle permisos
    if (object["tipo"] == "archivo") {
        
        // Revisar que esten los atributos propios de un archivo
        if (!object.contains("contenido") || !object.contains("permisos")){
            printf("Objeto invalido saltado, le falta contenido o permisos: %s\n", object.dump().c_str());
            return;
        }
        
        // Crear el archivo
        FileWriter fileWriter;
        if (fileWriter.checkFile(fullRoute)){
            printf("El archivo ya existe en %s, saltando\n", fullRoute.c_str());
            return;
        }
        fileWriter.open(fullRoute);
        fileWriter.write(object["contenido"]);
        fileWriter.close();

        // Obtener los permisos del archivo y guardar los flags
        std::string flags = "a=";
        std::vector<std::string> permissions = object.at("permisos");
        for (const auto& p : permissions) {
            auto it = DirTree::permissionsMap.find(p);
            if (it != DirTree::permissionsMap.end())
                flags += it->second;
            else 
                printf("Permiso invalido %s en archivo %s, saltando permiso\n", p.c_str(), fullRoute.c_str());
        }
        
        // Si no hay permisos, establecer lectura y escritura por defecto:
        if (flags.size() == 2)
            flags = "a=rw";

        // Aplicar los permisos al archivo (si hay permisos definidos)
        std::string command = "chmod " + flags + " " + parentDir + "/" + name;
        if (system(command.c_str()) != 0) {
            printf("No se pudieron establecer los permisos con %s, dejando por defecto\n", command.c_str());
            fflush_unlocked(stdout);
        }
        printf("Archivo creado en %s\n", fullRoute.c_str());
    }
    // Si el archivo es un directorio crearlo y iterar sobre sus objetos
    else if (object["tipo"] == "directorio") {
    
        // Revisar que esten los atributos propios de un directorio y sean validos
        if (!object.contains("objetos"))
            return (void)printf("Carpeta invalida saltada, le falta el atributo objetos: %s\n", object.dump().c_str());
        if (!object["objetos"].is_array())
            return (void) printf("La carpeta %s tiene objetos invalidos, saltando hijos\n", fullRoute.c_str());
        
        std::string command = "(mkdir " + parentDir + "/" + name + ") > /dev/null 2>&1";
    
        // Crear la carpeta
        if (system(command.c_str())){
            printf("No se pudo crear el directorio en %s, saltando\n", fullRoute.c_str());
            fflush_unlocked(stdout);
            return;
        }
        
        printf("Carpeta creada: %s\n", (parentDir + "/"+ name).c_str());
        
        // Crear recursivamente los objetos dentro de la carpeta
        // #pragma omp parallel for
        for (const auto& contents : object["objetos"]) 
            makeObjects(parentDir + "/" + name, contents);
    }
    else
        printf("Saltando... %s (tipo invalido)\n",object.dump().c_str());
};

void DirTree::createDir() {

    // Validar que se pueda comenzar el proceso
    if (!js.contains("dirBase") || !js.contains("objetos") || !js["objetos"].is_array())
        return (void)printf("El objeto base al menos debe contener los campos 'dirBase' y 'objetos' correctos.\n");
    printf("Revisando si existe directorio base...\n");
    FileReader fileReader;
    if (fileReader.checkDirectory(js["dirBase"]))
        return (void)printf("El directorio base '%s' ya existe, elige otro!\n", ((std::string) js["dirBase"]).c_str());
    
    // Crear el directorio base
    std::string cmdCrearDirBase = "mkdir " + (std::string)js["dirBase"];
    if (system(cmdCrearDirBase.c_str()) != 0)
        return (void) printf("No se pudo crear el directorio base, abortando!\n");
    
    // Comenzar a iterar con una funcion recursiva por cada objeto
    printf("Comenzando creacion...\n");
    for (const auto& obj : js["objetos"]) 
        makeObjects(js["dirBase"], obj);
}