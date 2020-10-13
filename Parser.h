#include <map>
#include <regex>
#include <iostream>
#include <fstream>

class Parser
{
private:
    static const std::map <std::string, std::string> parseFromString(std::string inputString);
public:
    static const std::map <std::string, std::string> parseJson(const std::string& json);
    static const std::map <std::string, std::string> parseJson(std::istream& jsonFile);
};