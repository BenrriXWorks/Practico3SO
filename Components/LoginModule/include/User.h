#include <string>
#include <time.h>

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
    std::string encrypt_user();
};