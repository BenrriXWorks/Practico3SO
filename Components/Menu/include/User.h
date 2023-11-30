#include <string>
#include "Functions.h"
#pragma once

class User 
{
private: 
    std::string username;
    std::string type;
    unsigned long permissions;
public:
    User(std::string name, std::string type, ulong permCode): username(name), type(type), permissions(permCode){}
    inline std::string getUsername() const {return username;}
    inline std::string getType() const {return type;}
    inline unsigned long getPermissionsCode() const {return permissions;}
    User(){username="",type="",permissions=0;}
    static User decodeUser(const std::string& response);
};