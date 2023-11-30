#include "../../include/User.h"

std::string User::encrypt_user(){
    srand(time(NULL));
    int encryptionKey = rand()%4 + 1;
    std::string info = getUsername() + " " + getType() + " " + std::to_string(getPermissionsCode());
    for (size_t i = 0; i < info.size(); i++)
        info[i] -= encryptionKey;
        
    return std::to_string(encryptionKey) + "-" + info;
}
