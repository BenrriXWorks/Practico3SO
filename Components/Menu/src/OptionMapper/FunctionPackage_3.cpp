#include "../../include/FunctionPackage_3.h"
using namespace std;

void crearArchivo(){

    fputs("FunPac_3\n",stdout);

    // Revisar si la variable de entorno existe y si el archivo termina con .txt
    ArgumentsLoader args = *ArgumentsLoader::getInstance();
    string pathCrear = args['f'];
    if (pathCrear == ""){
        fputs("crearArchivo:\n No se encontro la variable de entorno '-f'\n",stdout);
        return;
    }
    if (args['f'].substr(args['f'].size()-4) != ".txt"){
        printf("crearArchivo:\n Esta funcion esta restringida para archivos .txt\n");
        return;
    }

    FileReader fileReader;
    if (fileReader.open(pathCrear)){
        printf("crearArchivo:\n El archivo %s ya existe!\n",pathCrear.c_str());
        fileReader.close();
        return;
    }
    FileWriter fileWriter;
    if (!fileWriter.open(pathCrear)){
        printf("crearArchivo:\n No se pudo crear el archivo en {%s}!\n",pathCrear.c_str());
        return;
    }
    printf("crearArchivo: Se ha creado el archivo en %s\n",args['f'].c_str());
}

void agregarTexto(){

    fputs("FunPac_3 ",stdout);

    // Revisar si las variables de entorno necesarias existen
    ArgumentsLoader args = *ArgumentsLoader::getInstance();
    if (args['f'] == ""){
        fputs("agregarTexto:\n No se encontro la variable de entorno '-f'\n",stdout);
        return;
    }
    if (args['t'] == ""){
        fputs("agregarTexto:\n No hay texto con -t para agregarle al archivo!\n",stdout);
        return;
    }

    // Por seguridad, revisar que el archivo termine en .txt
    if (args['f'].substr(args['f'].size()-4) != ".txt"){
        printf("agregarTexto:\n Esta funcion esta restringida para archivos .txt\n");
        return;
    }
    FileReader fr;
    if (!fr.open(args['f'])){
        printf("agregarTexto:\n Por seguridad, el archivo -f {%s} debe existir como .txt previamente\n",args['f'].c_str());
        return;
    }
    fr.close();

    FileWriter fw;
    if (!fw.openAppend(args['f'])){
        printf("agregarTexto:\n No se pudo abrir el archivo en {%s}\n",args['f'].c_str());
        return;
    }
    fw.writeLine(args['t']);
    fw.close();
    printf("agregarTexto:\n Se ha escrito {%s} en {%s}\n",args['t'].c_str(),args['f'].c_str());
}