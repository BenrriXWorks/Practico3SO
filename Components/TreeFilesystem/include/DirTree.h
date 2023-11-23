#include <string>
#include "FileReader.h"
#include "FileWriter.h"
#include "json.hpp"

#pragma once

// Clase wrapper que envuelve un json dir
class DirTree
{
private:
    nlohmann::json js;

public:
    // Map con los permisos de los archivos
    static std::map<std::string, char> permissionsMap;
    // Construye el contenedor desde un archivo
    static DirTree* fromFile(std::string path, std::string extension);
    // Devuelve el js contenido por este wrapper
    inline nlohmann::json getjs() {return js;}
    // Crea los directorios guardados en el js del contenedor
    void createDir();
    // Almacena un js en el contenedor del objeto
    inline void setjs(nlohmann::json JSON) {js = JSON;};
};

