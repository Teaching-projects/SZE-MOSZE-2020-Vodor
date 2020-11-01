#include "JSON.h"

const JSON JSON::parseFromString(std::string inputString){
    static const std::regex parseRegex("\\s*\"([\\w]*)\"\\s*:\\s*\"?([\\s\\w\\.]*)\"?\\s*[,}]\\s*");
    std::smatch matches;
    std::map<std::string,std::string> attributes;
    std::string errMsg;
    if (inputString.substr(0,1) != "{"){
        errMsg = "Error in file: missing { from the top.";
        throw ParseException(errMsg); 
    }
    else if (inputString.substr(inputString.size()-1, 1) != "}"){
        errMsg = "Error in file: missing } from the bottom.";
        throw ParseException(errMsg); 
    }

    while(std::regex_search(inputString, matches, parseRegex)){
        if (matches[1] == "") {
            errMsg = "Error in file: incorrect key.";
            throw ParseException(errMsg); 
        }

        else if (matches[2] == "") {
            errMsg = "Error in file: incorrect value.";
            throw ParseException(errMsg); 
        }

        else
        {
            attributes[matches[1]] = matches[2];
            inputString = matches.suffix().str();
        }            
    }
        return JSON(attributes);
}


const JSON JSON::parseFromFile(const std::string& json) {
    std::smatch matches;

    static const std::regex fileNameRegex("([\\w]*).json$");
    if (std::regex_search(json, matches, fileNameRegex))
    {
        std::ifstream jsonFile;
        jsonFile.open(json);
        if (jsonFile.fail()) throw ParseException(json + " does not exist!");
        else
        {
           std::map<std::string, std::string> toReturn = parseJson(jsonFile).data;
           jsonFile.close();
           return JSON(toReturn);
        }
    }
    else return parseFromString(json);
    
}

const JSON JSON::parseJson(std::istream& jsonFile) {
    std::string jsonLine;
    std::string json = ""; 

    while (getline(jsonFile, jsonLine))
        json += jsonLine;

    return parseFromString(json);
}

const int JSON::count(const std::string& key){
    if (data.find(key) != data.end()) return 1;
    else return 0;
}