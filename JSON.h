#ifndef JSON_H
#define JSON_H

/*!
 * \class JSON
 * 
 * \brief JSON class
 * 
 * A Parse-olásért felelős osztály.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 4.0
 * 
 * \date 2020/11/02 13:22
 * 
 * Created on 2020/11/02 13:22
 */

#include <map>
#include <regex>
#include <iostream>
#include <fstream>
#include <variant>
#include <cctype>
#include <algorithm>

using jsonData = std::map <std::string, std::variant<std::string, int, double>>;

class JSON
{
private:
    jsonData b_data; ///< Adatoknak létrehozott map.
public:
    /*! \brief JSON konstruktor
 	*         
 	*  
	*  \param data [in] adat.
 	*/
    JSON(jsonData data) : b_data(data){}
    /// Ez a függvény a String értéket parse-olja.
    static const JSON parseFromString(std::string inputString);
    /// Ez a függvény a Fájlt parse-olja.
    static const JSON parseFromFile(const std::string& json);
    /// Ez a függvény a .json file parse-olja.
    static const JSON parseJson(std::istream& jsonFile);
    /// Ez a függvény vizsgálja adott key benne van-e mapben.
    const int count(const std::string& key);
    /// Ez a függvény visszaad egy valuet a key alapján.
    template <typename T> T get(const std::string& key){
        if (!count(key)) throw ParseException("Key does not exist in map!");
        else return std::get<T>(b_data[key]);
    }

    class ParseException : public std::runtime_error{
    public:
         /// Ez a függvény hiba üzentet ad.
        ParseException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };
};

#endif