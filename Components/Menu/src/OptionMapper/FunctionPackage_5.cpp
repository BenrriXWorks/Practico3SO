#include "../../include/FunctionPackage_5.h"

void crearCarpetasArbol(){

}

void crearCarpetasLista(){
    
}

void mostrarGrafico(){
    
    // Identificador de donde estamos y cargar archivos de entorno a usar
    printf("FunPac_5:\n");
    EnvLoader env = *EnvLoader :: getInstance();
    std::string rutaArchivoPuntos = env["PLOTTER_INPUT_ROUTE"];
    std::string rutaEjecutablePlotter = env["PLOTTER_EXEC_ROUTE"];

    // Si falta alguna variable de entorno, avisar y retornar
    if (rutaEjecutablePlotter == "")
        return (void) fputs_unlocked("mostrarGrafico: Falta el ejecutable \"PLOTTER_EXEC_ROUTE\" en .env", stderr);
    if (rutaArchivoPuntos == "") 
        return (void) fputs_unlocked("mostrarGrafico: Falta la ruta del archivo \"PLOTTER_INPUT_ROUTE\" en .env\n", stderr);
    
    // Ejecutar
    std::string command = rutaEjecutablePlotter + " " + rutaArchivoPuntos;
    printf("Comando ejecutado: %s\n", command.c_str());
    if (system(command.c_str()))
        printf("mostrarGrafico: Hubo un error en la ejecucion\n");
    
}