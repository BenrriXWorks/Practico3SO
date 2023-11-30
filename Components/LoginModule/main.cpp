#include <cstdio>
#include <cstdlib>
#include "include/UserManager.h"
#include "ArgumentsLoader.h"

using namespace std;

int main(int argc, char** argv){

    if (argc != 4) return (
        printf("Error: Login: Los argumentos ingresados son invalidos, deben ser {user} {usersPath} {permissionsPath}\n"),
        EXIT_FAILURE
        );
    string username = argv[1], pathUsers = argv[2], pathPermissions = argv[3];

    UserManager um = UserManager::getInstance();
    um.loadDatabase(pathUsers,pathPermissions);

    User* user = um.login(username);
    if(user == nullptr) 
        return(printf("Error: Login: El usuario {%s} no existe!\n",username.c_str()),EXIT_FAILURE);

    printf("%s\n",(string("Success:") + user->encrypt_user()).c_str());

    return EXIT_SUCCESS;

}