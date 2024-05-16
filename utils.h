#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

class Utils{
    public:
    static bool isANumber(std::string);
    static std::vector<std::string> split(std::string, std::string);
    static bool isFloat(std::string);
};

#endif // UTILS_H
