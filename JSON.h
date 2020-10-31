#include <map>
#include <regex>
#include <iostream>
#include <fstream>

class JSON
{
private:
    std::map <std::string, std::string> data;
public:
    JSON(std::map <std::string, std::string> data) : data(data){}
    static const JSON parseFromString(std::string inputString);
    static const JSON parseFromFile(const std::string& json);
    static const JSON parseJson(std::istream& jsonFile);
    const int count(const std::string& key){ return data.count(key); }
    
    template <class T> T get(const std::string& key){
        return data[key];
    }
    
    bool checkIfKeyExists(const std::string& key);

    class ParseException : public std::runtime_error{
    public:
        ParseException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };
};