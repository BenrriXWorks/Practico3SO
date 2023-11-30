#include "../../include/MenuObj.h"
using namespace std;

map<uint8_t,Option> MenuObj::functions = map<uint8_t,Option>();

void testFunc();

void MenuObj::display(User user){

    functions = OptionMapper::loadOptions();
    // Caso -2: Solo desplegar informacion inicial, no ejecutar nada
    // Caso -1: Entrada invalida
    // eoc: Iniciar funcion requerida si es posible.
    // Se puede causar un caso -2 si la funcion que se llama hace setenv("RESTART_MENU?","1",1);

    int opt = -2;
    do {
        setenv("RESTART_MENU?","0",1);
        clearWindow();
        printf("Bienvenido %s! [%s]\tPID=%d\n",user.getUsername().c_str(),user.getType().c_str(),getpid());
        // printf("opt=%d, Permissions=%lu\n",opt,user.getPermissionsCode()); // Informacion de debug
        fputc('\n',stdout);

        // Revisar que sea una opcion valida, que la opcion exista y que el usuario tenga el permiso.
        if (opt == -1) printf("Por favor ingrese una opcion valida\n\n");
        else if (opt != -2 && functions.find(opt) == functions.end()) printf("La opcion especificada no existe!\n\n");
        else if (opt != -2 && (user.getPermissionsCode() & (1<<opt)) == 0) printf("No tienes permiso para realizar esta accion!\n\n");
        else if (opt != -2){
            fputs("<===================salida=====================>\n",stdout);
            functions.at(opt)();
            fputs("<==============================================>\n\n",stdout);
        }
        
        fputs("Por favor escoja una opcion: \n",stdout);
        for (const auto& opt : functions)
            if ((user.getPermissionsCode() & (1<<opt.first)))
                fputs(opt.second.toString().c_str(),stdout);
        printf("Opcion: ");
    
        string input;
        if (getenv("RESTART_MENU?") == string("0")){
            getline(cin,input);
            opt = input.find_first_not_of("0123456789") != string::npos || input.empty() ? -1 : stoi(input); 
        }
        else
            opt = -2;
    } while (true);
}

void testFunc(){
    printf("Funcion ejecutada\n");
}
