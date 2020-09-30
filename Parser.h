#include <map>
#include <regex>

class Parser
{
public:
    std::map <std::string, std::string> parseJson(std::string json);
    std::map <std::string, std::string> parseJson(std::istream& jsonFile);
};