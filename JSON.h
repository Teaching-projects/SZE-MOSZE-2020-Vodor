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

class JSON
{
private:
    std::map <std::string, std::string> data; ///< Adatoknak létrehozott map.
public:
    /*! \brief JSON konstruktor
 	*         
 	*  
	*  \param data [in] adat.
 	*/
    JSON(std::map <std::string, std::string> data) : data(data){}
    /// Ez a függvény a String értéket parse-olja.
    static const JSON parseFromString(std::string inputString);
    /// Ez a függvény a Fájlt parse-olja.
    static const JSON parseFromFile(const std::string& json);
    /// Ez a függvény a .json file parse-olja.
    static const JSON parseJson(std::istream& jsonFile);
    /// Ez a függvény viszgálja adott key benne van-e mapben.
    const int count(const std::string& key);
    /// Ez a függvény visszaad egy valuet a key alapján.
    template <class T> T get(const std::string& key){
        return data[key];
    }

    class ParseException : public std::runtime_error{
    public:
         /// Ez a függvény hiba üzentet ad.
        ParseException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };
};

#endif