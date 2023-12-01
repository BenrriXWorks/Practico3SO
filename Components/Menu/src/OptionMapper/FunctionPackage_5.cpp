#include "../../include/FunctionPackage_5.h"

void crearCarpetasArbol(){

    // Ubicar la funcion en caso de errores
    printf("FunPac_5:\n");
    EnvLoader env = *EnvLoader :: getInstance();

    // Definir las variables de entorno necesarias
    std::map<const char*, std::string> requieredEnv {
        {"INPUT_FILE", "TREE_FILESYSTEM_INPUT_ROUTE"},
        {"EXECUTABLE", "TREE_FILESYSTEM_EXEC_ROUTE"}
    };

    // Revisar que no falten variables de entorno
    for (const auto& reqEnv : requieredEnv)
        if (env[reqEnv.second] == "")
            return (void) printf("crearCarpetasArbol: Falta la variable de entorno %s\n", reqEnv.second.c_str());

    // Recibir las variables de entorno
    std::string ditRoute = env[requieredEnv["INPUT_FILE"]];
    std::string execRoute = env[requieredEnv["EXECUTABLE"]];

    // Ejecutar el comando
    std::string command = (execRoute + " " + ditRoute).c_str();
    printf("Comando ejecutado: %s\n", command.c_str());
    if (system(command.c_str()))
        printf("crearCarpetasArbol: Hubo un error en la ejecucion\n");
    
}

void crearCarpetasLista(){
    printf("FunPac_5:\n");
    EnvLoader env = *EnvLoader :: getInstance();

    std::map<const char*, std::string> requieredEnv {
        {"CIRCLE_EXEC", "DIR_CIRCLE_EXEC_ROUTE"},
        {"DIR_MAX", "DIR_MAX_CIRCLE_FILESYSTEM"},
        {"AR_MAX", "AR_MAX_CIRCLE_FILESYSTEM"}
    };

    // Revisar que no falten variables de entorno
    for (const auto& reqEnv : requieredEnv)
        if (env[reqEnv.second] == "")
            return (void) printf("crearCarpetasLista: Falta la variable de entorno %s\n", reqEnv.second.c_str());


    std::string rutaEjecutableDirCircle = env[requieredEnv["CIRCLE_EXEC"]];
    std::string maxDirectorios = env[requieredEnv["DIR_MAX"]];
    std::string maxArchivos = env[requieredEnv["AR_MAX"]];

    int bufferSize = 1024;
    char* inputFile = new char[bufferSize];
    clearWindow();
    fputs_unlocked("-- ACCION REQUERIDA --\nIngrese la ruta del archivo .dre: ", stdout);
    if (fgets_unlocked(inputFile, bufferSize, stdin) == nullptr) return (void) fputs_unlocked("No se pudo leer la entrada\n", stdout);
    fputs_unlocked("Entrada recibida\n\n", stdout);
    


    
    std::string command = rutaEjecutableDirCircle + " " + inputFile + " " + maxDirectorios + " " + maxArchivos;
    printf("Comando ejecutado= %s\n",command.c_str());
    if(system(command.c_str())){
        printf("crearCarpetasLista: Hubo un error en la ejecucion.\nPresione enter para continuar...\n");
    };
}

void mostrarGrafico(){

    // Identificador de donde estamos y cargar archivos de entorno a usar
    printf("FunPac_5:\n");
    EnvLoader env = *EnvLoader :: getInstance();
    std::map<const char*, std::string> requieredEnv {
        {"PLOTTER_EXEC","PLOTTER_EXEC_ROUTE"},
        {"PADDING", "PLOTTER_PADDING"},
        {"WINDOW_SIZE", "PLOTTER_WINDOW_SIDE_SIZE"}
    };

    // Revisar que no falten variables de entorno
    for (const auto& reqEnv : requieredEnv)
        if (env[reqEnv.second] == "")
            return (void) printf("mostrarGrafico: Falta la variable de entorno %s\n", reqEnv.second.c_str());

    // Guardar las variables de entorno
    std::string rutaEjecutablePlotter = env[requieredEnv["PLOTTER_EXEC"]];
    std::string padding = env[requieredEnv["PADDING"]];
    std::string windowSize = env[requieredEnv["WINDOW_SIZE"]];

    // Preguntar la ruta del archivo de entrada por consola
    int bufferSize = 1024;
    char* inputFile = new char[bufferSize];
    clearWindow();
    fputs_unlocked("-- ACCION REQUERIDA --\nIngrese la ruta del archivo de puntos: ", stdout);
    if (fgets_unlocked(inputFile, bufferSize, stdin) == nullptr) return (void) fputs_unlocked("No se pudo leer la entrada\n", stdout);
    fputs_unlocked("Entrada recibida\n\n", stdout);
    setenv("RESTART_MENU?", "1", true); // Reiniciar el menu igual que como el buscador antes

    // Ejecutar el plotter
    std::string command = "WINDOW_SIZE=" + windowSize + " PADDING=" + padding + " " + rutaEjecutablePlotter + " " + inputFile;
    printf("Comando ejecutado: %s\n", command.c_str());
    if (system(command.c_str())){
        printf("mostrarGrafico: Hubo un error en la ejecucion.\nPresione enter para continuar...\n");
        getchar_unlocked();
    }
    
}