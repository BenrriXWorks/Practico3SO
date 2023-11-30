#include <cstdio>
#include <cstdlib>
#include "ArgumentsLoader.h"
#include "EnvLoader.h"
#include "Functions.h"
#include "User.h"
#include "MenuObj.h"
using namespace std;

#define RESPONSE_FILE string(".LOGIN_RESPONSE.dump")

int main(int argc, char** argv){

    // Leer los argumentos y las variables del .env
    ArgumentsLoader& args = *ArgumentsLoader::getInstance();
    if (!args.loadArgs(argc, argv, "i:o:f:u:v:t:","u")){
        printf("Menu: Los argumentos no han sido cargados correctamente.\n");
        return EXIT_FAILURE;
    };
    EnvLoader& env = *EnvLoader::getInstance();
    env.loadEnv(".env");

    // Abrir el sistema de login y usar un archivo temporal para recibir la respuesta.
    string loginLaunch = string() + "Components/LoginModule/main " + args['u'] + " "
      + env["USERS_DB"] + " " + env["PERMISSIONS_DB"] + " > " + RESPONSE_FILE;
    if (system(loginLaunch.c_str()) != 0){
        printf("Menu: No se ha podido iniciar sesion\n");
        printf("REVISAR ARCHIVO .DUMP PARA MAS INFORMACION\n");
        return EXIT_FAILURE;
    }

    // Leer la respuesta del login y decodificar el token.
    FileReader fr;
    if (!fr.open(RESPONSE_FILE)){
        printf("Menu: No se ha podido leer el token de incio de sesion\n");
        return EXIT_FAILURE;
    }
    string response = fr.read();
    if (system((string() + "rm " + RESPONSE_FILE).c_str()))  // ELiminar el token generado
        printf("Removiendo el token de inicio de sesion\n");
  
    MenuObj menu;
    menu.display(User::decodeUser(response));

    return EXIT_SUCCESS;

}

