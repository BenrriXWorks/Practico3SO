#include <memory>
#include "User.h"
#include "robin_hood.h"
#include "FileReader.h"
#include "FileWriter.h"
#include <unordered_map>
#include "Functions.h"

class UserManager
{
private:
    static const std::unique_ptr<UserManager> instance;
    static std::unordered_map<std::string, ulong> typeToPermissions;
    static std::unordered_map<std::string, User> UsersDatabase;
    UserManager(){};
public:
    static UserManager& getInstance() {return *instance;};
    User* login(std::string username);
    bool loadDatabase(std::string pathUsers, std::string pathProfiles);
    bool addUser(User user, std::string pathUsers);
};
