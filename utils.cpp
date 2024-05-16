#include "utils.h"
#include <string>
#include <vector>
#include <iostream>

bool Utils::isANumber(std::string value){
    try{
        std::stoi(value);
        return true;
    }
    catch(std::exception &ex){
        return false;
    }
}

bool Utils::isFloat(std::string value){
    if (value.find(".")!=-1){
        return true;
    }
    return false;
}

std::vector<std::string> Utils::split(std::string source, std::string splitter) {
    std::vector<std::string> splitted_sources;
    std::string splitted_source = "";
    int end_index = 0;
    int splitter_len = splitter.length();
    while ((end_index = source.find(splitter)) != -1) {
        std::cout << "Looping" << std::endl;
        splitted_sources.push_back(source.substr(0, end_index));
        //splitted_sources.push_back(range(source ,0, end_index, 1));
        source = source.substr(end_index + splitter_len);
        //source = range(source, end_index+splitter_len, source.length(), 1);
    }
    splitted_sources.push_back(source);
    std::cout << "Loop Completed" << std::endl;
    return splitted_sources;
}
