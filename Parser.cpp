#include "Parser.h"

const std::map <std::string, std::string> Parser::parseFromString(std::string inputString){
    static const std::regex parseRegex("\\s*\"([\\w]*)\"\\s*:\\s*\"?([\\w\\.]*)\"?\\s*[,}]\\s*");
    std::smatch matches;
    std::map<std::string,std::string> attributes;
    std::string errMsg;
    if (inputString.substr(0,1) != "{"){
        errMsg = "Error in file: missing { from the top.";
        throw errMsg; 
    }
    else if (inputString.substr(inputString.size()-1, 1) != "}"){
        errMsg = "Error in file: missing } from the bottom.";
        throw errMsg; 
    }

    while(std::regex_search(inputString, matches, parseRegex)){
        if (matches[1] == "") {
            errMsg = "Error in file: incorrect key.";
            throw errMsg; 
        }

        else if (matches[2] == "") {
            errMsg = "Error in file: incorrect value.";
            throw errMsg; 
        }

        else
        {
            attributes[matches[1]] = matches[2];
            inputString = matches.suffix().str();
        }            
    }
        return attributes;
}


const std::map <std::string, std::string> Parser::parseJson(const std::string& json) {
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
    else return parseFromString(json);
    
}

const std::map <std::string, std::string> Parser::parseJson(std::istream& jsonFile) {
    std::string jsonLine;
    std::string json = ""; 

    while (getline(jsonFile, jsonLine))
        json += jsonLine;

    return parseFromString(json);
}