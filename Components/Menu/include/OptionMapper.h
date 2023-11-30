#include "Option.h"
#include "ArgumentsLoader.h"
#include "EnvLoader.h"
#include "robin_hood.h"
#include "FileReader.h"
#include <functional>
#include <map>

#include "FunctionPackage_1.h"
#include "FunctionPackage_2.h"
#include "FunctionPackage_3.h"
#include "FunctionPackage_4.h"
#include "FunctionPackage_5.h"


class OptionMapper
{
private:
    static robin_hood::unordered_flat_map<std::string, std::function<void(void)>> functions;
public:
    static std::map<uint8_t, Option> loadOptions();
};