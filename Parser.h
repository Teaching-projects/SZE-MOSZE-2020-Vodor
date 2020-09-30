#include <map>
#include <regex>

class Parser{
    std::map<std::string,std::string> attributes;
    std::smatch matches;
    public:
        std::map <std::string, std::string> parseJson(std::string json);
        //std::map <std::string, std::string> parseJson(std::istream& jsonFile);
};