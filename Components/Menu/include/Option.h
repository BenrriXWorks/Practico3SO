#include <functional>
#include <string>
#pragma once

class Option
{
private:
    uint8_t option;
    std::string text;
    std::function<void (void)> f;
public:
    Option(uint8_t option, std::string text, std::function<void (void)> f) : option(option), text(text), f(f){}
    inline const std::string toString() const {return std::to_string(option) + ") " + text + "\n";}; 
    Option(): option(-1), text(""), f([](){}) {};
    inline void operator()(){f();};
};