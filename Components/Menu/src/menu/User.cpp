#include "../../include/User.h"
using namespace std;

User User::decodeUser(const std::string& response){
    pair<string,string> token = split1(response.substr(response.find(":") + 1),'-');
    uint8_t decoder = stoi(token.first);
    string userData = token.second;
    for (size_t i = 0 ; i < userData.size(); i++)
        userData[i] += decoder;
    auto info = split(userData,' ');
    return User(info[0],info[1],stoul(info[2]));
}