#include <map>
#include <regex>
#include <iostream>
#include <fstream>

class Parser
{
public:
    const std::map <std::string, std::string> parseJson(std::string json);
    const std::map <std::string, std::string> parseJson(std::istream& jsonFile);
};