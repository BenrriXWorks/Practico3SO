#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "include/json.hpp"

auto print = [](const char* text){fputs_unlocked(text, stdout), fputs_unlocked("\n",stdout);};

int main(int argc, char** argv){

    print("hello world");

    auto j = R"({"happy":"true", "pi": 3.1415926})"_json;
    printf("Happy: %s\n", std::string(j["happy"]).c_str());
    printf("Pi: %f\n", (float)(j["pi"]));

    return EXIT_SUCCESS;
}