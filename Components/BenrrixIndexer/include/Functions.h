#include <vector>
#include <string>
#pragma once

inline bool inRange(int i, int l, int r){return i>=l && i<=r;}

std::vector<std::string> split(const std::string word, char delim);
std::pair<std::vector<int>,bool> splitInt(const std::string word, char delim);
std::string strip(std::string line, char c);
std::string strip(std::string line);
std::string stripAllOf(std::string line, std::string chars);
std::string soloMin(std::string line);