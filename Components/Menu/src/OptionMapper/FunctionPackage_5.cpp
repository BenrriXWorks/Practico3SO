#include "../../include/FunctionPackage_5.h"

void crearCarpetasArbol(){

}

void crearCarpetasLista(){
    printf("FunPac_5:\n");
    EnvLoader env = *EnvLoader ::getInstance();

    std::map<const char*, std::string> requieredEnv {
        {"IMPUT_FILE","DIR_CIRCLE_INPUT_ROUTE"},
        {"CIRCLE_EXEC", "DIR_CIRCLE_EXEC_ROUTE"},
        {"DIR_MAX", "DIR_MAX_CIRCLE_FILESYSTEM"},
        {"AR_MAX", "AR_MAX_CIRCLE_FILESYSTEM"}
    };

    // Revisar que no falten variables de entorno
    for (const auto& reqEnv : requieredEnv)
        if (env[reqEnv.second] == "")
            return (void) printf("dirCircular: Falta la variable de entorno %s\n", reqEnv.second.c_str());


    std::string rutaArchivoDirCircle = env[requieredEnv["INPUT_FILE"]];
    std::string rutaEjecutableDirCircle = env[requieredEnv["CIRCLE_EXEC"]];
    std::string maxDirectorios = env[requieredEnv["DIR_MAX"]];
    std::string maxArchivos = env[requieredEnv["AR_MAX"]];

    
    std::string command = rutaEjecutableDirCircle + " " + rutaArchivoDirCircle + " " + maxDirectorios + " " + maxArchivos;
    printf("Comando ejecutado= %s\n",command.c_str());
    if(system(command.c_str()))
        printf("directorioCircular: Hubo un error en la ejecucion\n");
}

void mostrarGrafico(){

    // Identificador de donde estamos y cargar archivos de entorno a usar
    printf("FunPac_5:\n");
    EnvLoader env = *EnvLoader :: getInstance();
    std::map<const char*, std::string> requieredEnv {
        {"PLOTTER_EXEC","PLOTTER_INPUT_ROUTE"},
        {"INPUT_FILE", "PLOTTER_EXEC_ROUTE"},
        {"PADDING", "PLOTTER_PADDING"},
        {"WINDOW_SIZE", "PLOTTER_WINDOW_SIDE_SIZE"}
    };

    // Revisar que no falten variables de entorno
    for (const auto& reqEnv : requieredEnv)
        if (env[reqEnv.second] == "")
            return (void) printf("mostrarGrafico: Falta la variable de entorno %s\n", reqEnv.second.c_str());

    std::string rutaArchivoPuntos = env[requieredEnv["INPUT_FILE"]];
    std::string rutaEjecutablePlotter = env[requieredEnv["PLOTTER_EXEC"]];
    std::string padding = env[requieredEnv["PADDING"]];
    std::string windowSize = env[requieredEnv["WINDOW_SIZE"]];



    // Ejecutar
    std::string command = "WINDOW_SIZE=" + windowSize + " PADDING=" + padding + " " + rutaArchivoPuntos + " " + rutaEjecutablePlotter;
    printf("Comando ejecutado: %s\n", command.c_str());
    if (system(command.c_str()))
        printf("mostrarGrafico: Hubo un error en la ejecucion\n");
    
}