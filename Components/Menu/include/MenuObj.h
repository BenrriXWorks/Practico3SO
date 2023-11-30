#include "User.h"
#include <unistd.h>
#include "ArgumentsLoader.h"
#include "EnvLoader.h"
#include "Option.h"
#include <map>
#include "Functions.h"
#include "OptionMapper.h"

class MenuObj
{
private:
    static std::map<uint8_t,Option> functions;
public:
    void display(User user);

};