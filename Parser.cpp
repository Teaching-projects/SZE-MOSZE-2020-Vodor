#include "Parser.h"

std::map <std::string, std::string> Parser::parseJson(std::string json){
    //TODO: check if the string is a filename

    static const std::regex parseRegex("\\s*\"([\\w]*)\"\\s*:\\s*\"?([\\w]*)\"?\\s*[,}]\\s*");
    std::smatch matches;
    std::map<std::string,std::string> attributes;

    while(std::regex_search(json, matches, parseRegex)){
        attributes[matches[1]] = matches[2];
        json = matches.suffix().str();
    }

    return attributes;
}

std::map <std::string, std::string> Parser::parseJson(std::istream& jsonFile){
    std::string line;
    std::string json = ""; 
    while(getline(jsonFile,line))
        json += line;

    return parseJson(json);
}