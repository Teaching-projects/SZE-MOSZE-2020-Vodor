#include "Parser.h"

std::map <std::string, std::string> Parser::parseJson(std::string json){
    //TODO: check if the string is a filename

    attributes.clear();
    static const std::regex parseRegex("\\s*\"([\\w]*)\"\\s*:\\s*\"?([\\w]*)\"?\\s*[,}]\\s*");

    while(std::regex_search(json, matches, parseRegex)){
        attributes[matches[1]] = matches[2];
        json = matches.suffix().str();
    }

    return attributes;
}

/*Unit* Parser::parseJson(std::istream& jsonFile){
    TODO: finish this
}*/