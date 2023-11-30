#include "../../include/UserManager.h"
using namespace std;

const unique_ptr<UserManager> UserManager::instance(new UserManager);

unordered_map<string, ulong> UserManager::typeToPermissions = unordered_map<std::string, ulong>();
unordered_map<string, User> UserManager::UsersDatabase = unordered_map<string, User>();

User* UserManager::login(string username){
    auto it = UsersDatabase.find(username);
    return it == UsersDatabase.end() ? nullptr : &it->second;
};

bool UserManager::loadDatabase(std::string pathUsers, std::string pathProfiles){
    // Abrir los archivos
    FileReader fileUsers, fileProfiles;
    if (!fileUsers.open(pathUsers)) 
        return (printf("UserManager: No se pudo abrir el archivo de usuarios\n"), false);
    if (!fileProfiles.open(pathProfiles))
        return (printf("UserManager: No se pudo abrir el archivo de perfiles."),false);
    
    
    // Leer los perfiles
    for (const string& line : fileProfiles.readLines())
        if (!line.empty()) 
            try {
                const pair<string,string>& p = split1(line,';');
                if (!p.first.empty()){
                    if (p.second != "*")
                        for (const auto& perm : split(p.second,','))
                            typeToPermissions[p.first] |= (1<<stoi(perm)); 
                    else
                        typeToPermissions[p.first] = -2;
                }
           }
            catch(...){
                printf("UserManager: El formato del archivo de permisos en la linea {%s} es invalido\n",line.c_str());
                return false;
            }
        
    /*for (const auto& p : typeToPermissions){
        printf("%s: %lu\n",p.first.c_str(), p.second);
    }*/
    
    // Leer los usuarios
    for (std::string line : fileUsers.readLines())
        if (!line.empty()){
            try{
                const pair<string,string>& p = split1(line,',');
                if (!p.first.empty() && !p.second.empty() && (p.first.find_first_not_of("qwertyuiopasdfghjklzxcvbnm1234567890") != string::npos 
                    || !UsersDatabase.try_emplace(p.first, User(p.first,p.second,typeToPermissions.at(p.second)+1)).second))
                        printf("UserManager: El usuario de la linea {%s} no ha podido ser agregado.\n", line.c_str());
                //else printf("El usuario {%s} de tipo {%s} ha sido agregado\n",p.first.c_str(),p.second.c_str());
            }
            catch(...){
                printf("UserManager: El archivo de Usuarios no tiene el formato adecuado en la linea {%s}\n",line.c_str());
                return false;
            }
        }

    /*for (const auto& p : UsersDatabase){
        printf("%s: %s\n",p.first.c_str(), p.second.getType().c_str());
    }*/
    return true;
}

bool UserManager::addUser(User user, string pathUser){
    if (UsersDatabase.contains(user.getUsername()))
        return(printf("UserManager: El usuario {%s} ya existe!",user.getUsername().c_str()),false);
    UsersDatabase[user.getUsername()] = user;
    FileWriter fw;
    if (!fw.openAppend(pathUser)){
        printf("El usuario {%s} no ha podido ser guardado en el archivo local en {%s}\n",user.getUsername().c_str(),pathUser.c_str());
        return false;
    }
    fw << user.getUsername() + "," + user.getType() + "\n";
    return true;
}
