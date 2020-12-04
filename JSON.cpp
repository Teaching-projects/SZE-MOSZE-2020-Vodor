#include "JSON.h"

const JSON JSON::parseFromString(std::string inputString){
    static const std::regex parseRegex("\\s*\"([\\w-]*)\"\\s*:\\s*\"?([\\s\\w\\.-\\/]*)\"?\\s*[,}]\\s*");
    static const std::regex regexForList("\\s*\"([\\w]*)\"\\s*:\\s*\"?\\[?\\s*([\\w\\.\"?,?\\s*]*)\"?\\s*[,\\]}]");
    std::smatch matches;
    std::smatch matchList;
    jsonData attributes;
    std::string errMsg;
    std::string value;
    int pos;
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
            value = matches[2];

            if (!value.empty() && std::all_of(value.begin(), value.end(), [](char c){return std::isdigit(c);})) attributes[matches[1]] = std::stoi(value);
            else if (!value.empty() && std::all_of(value.begin(), value.end(), [](char c){return ((std::isdigit(c) || c == '.') ? true : false);})) attributes[matches[1]] = std::stod(value);
            else attributes[matches[1]] = value;
            pos = inputString.find(matches.str());
            inputString.erase(pos, matches.str().length());
        }            
    }
    while(std::regex_search(inputString, matchList, regexForList)){
        value = matchList[2];
        while (value.find(",")!=std::string::npos)
            value.erase(value.find(","),1);
            
        while(value.find("\"")!= std::string::npos)
            value.erase(value.find("\""),1);

        attributes[matchList[1]]=value;
        inputString = matchList.suffix().str();
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
           jsonData toReturn = parseJson(jsonFile).b_data;
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
    if (b_data.find(key) != b_data.end()) return 1;
    else return 0;
}