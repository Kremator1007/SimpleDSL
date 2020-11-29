#pragma once
#include <algorithm>
#include <string>

bool isNotSpace(char ch){
    return ch != ' ';
}
inline std::string ltrim(std::string toTrim){
    toTrim.erase(toTrim.begin(), std::find_if(toTrim.begin(), toTrim.end(), isNotSpace));
    return toTrim;
}

inline std::string rtrim(std::string toTrim){
    toTrim.erase(std::find_if(toTrim.rbegin(), toTrim.rend(), isNotSpace).base(), toTrim.end());
    return toTrim;
}
inline std::string trim(std::string toTrim){
    return ltrim(rtrim(toTrim));
}