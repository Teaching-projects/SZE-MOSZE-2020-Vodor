#include "Parser.h"

const std::map <std::string, std::string> Parser::parseJson(std::string json) {
    static const std::regex parseRegex("\\s*\"([\\w]*)\"\\s*:\\s*\"?([\\w\\.]*)\"?\\s*[,}]\\s*");
    std::smatch matches;
    std::map<std::string,std::string> attributes;

    static const std::regex fileNameRegex("([\\w]*).json$");
    if (std::regex_search(json, matches, fileNameRegex))
    {
        std::ifstream jsonFile;
        jsonFile.open(json);
        if (jsonFile.fail()) throw json + " does not exist!";
        else
        {
           attributes = parseJson(jsonFile);
           jsonFile.close();
           return attributes;
        }
    }
    else
    {
        while(std::regex_search(json, matches, parseRegex))
        {
            attributes[matches[1]] = matches[2];
            json = matches.suffix().str();
        }
        return attributes;
    }
}

const std::map <std::string, std::string> Parser::parseJson(std::istream& jsonFile) {
    std::string jsonLine;
    std::string json = ""; 

    while (getline(jsonFile, jsonLine))
        json += jsonLine;

    return parseJson(json);
}