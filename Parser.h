/*!
 * \class Parser
 * 
 * \brief Parser class
 * 
 * Ez az osztály a bemeneti fájlok parzolásáért felelős.
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 3.3
 * 
 * \date 2020/10/26 9:00
 * 
 * Created on 2020/10/26 9:00
 */


#include <map>
#include <regex>
#include <iostream>
#include <fstream>

class Parser
{
public:
    /// JSON formátumú string parzolására alkalmas függvény.
    static const std::map <std::string, std::string> parseFromString(std::string inputString/** [in] karakterlánc, ami egy JSON formátumot tartalmaz */);
    /// JSON fájl parzolására alkalmas függvény.
    static const std::map <std::string, std::string> parseJson(const std::string& json/** [in] a JSON fájl elérési útja */);
    /// JSON fájl parzolására alkalmas függvény.
    static const std::map <std::string, std::string> parseJson(std::istream& jsonFile/** [in] a beolvasott JSON fájlt tartalmazó istream */);
};