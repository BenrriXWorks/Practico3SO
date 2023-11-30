#include "../../include/OptionMapper.h"

robin_hood::unordered_flat_map<std::string, std::function<void(void)>> OptionMapper::functions
    = robin_hood::unordered_flat_map<std::string, std::function<void(void)>>();

std::map<uint8_t, Option> OptionMapper::loadOptions(){
    if (functions.empty()){
        functions["salir"] = [](){clearWindow();printf("Adios %s!\n",(*ArgumentsLoader::getInstance())['u'].c_str());exit(0);};
        functions["createIndexFolder"] = createIndexFolder;
        functions["invertIndexFolder"] = invertIndexFolder;
        functions["sumatoria"] = sumatoria;
        functions["promedio"] = promedio;
        functions["moda"] = moda;
        functions["cuentaElementos"] = cuentaElementos;
        functions["verArgumentos"] = verArgumentos;
        functions["crearArchivo"] = crearArchivo;
        functions["agregarTexto"] = agregarTexto;
        functions["contarPalabras"] = contarPalabras;
        functions["llamarBuscador"] = llamarBuscador;
        functions["crearCarpetasArbol"] = crearCarpetasArbol;
        functions["crearCarpetasLista"] = crearCarpetasLista;
        functions["mostrarGrafico"] = mostrarGrafico;
    }
    EnvLoader env = *EnvLoader::getInstance();
    if (env["OPTIONS_DB"] == ""){
        printf("Menu (OptionMapper): No se puede acceder a OPTIONS_DB en el .env\n");
        exit(0);
    }
    FileReader fr;
    if (!fr.open(env["OPTIONS_DB"])){
        printf("Menu (OptionMapper): No se pudo leer el archivo de base de datos de opciones\n");
        exit(0);
    };

    std::map<uint8_t, Option> optionMap = std::map<uint8_t, Option>();
    for (const auto& line : fr.readLines()) try {
        if (!line.empty()){
            auto p = split(line,',');
            if (!optionMap.try_emplace(stoi(p[0]),Option(stoi(p[0]),p[1],functions.at(p[2]))).second)
                printf("Menu (OptionMapper): La opcion {%s} esta en conflicto con otra opcion, saltando\n", line.c_str());
        }
    }catch(...){
        printf("Menu (OptionMapper): La linea del archivo de opciones {%s} no cumple el formato requerido o la funcion no existe\n",line.c_str());
        exit(0);
    }
    
    return optionMap;
}
