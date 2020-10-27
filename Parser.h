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
    /// JSON fájlból beolvasott karakterlánc parzolását végző függvény.
    /// Hibát dob, amennyiben hiányos, vagy sérült a fájl. Pl.: hiányoznak kulcsok adott párokból, vagy nincsenek meg a kezdő, és/vagy záró karakterek
    /*!
    \return Visszaadja a JSON fájlból beolvasott értékeket egy mapben.
    */
    static const std::map <std::string, std::string> parseFromString(std::string inputString/** [in] JSON formátumú karakterlánc */);
    /// Egy fájl elérési útja alapján parzoló függvény. Működése során meghívja a istream-et váró overloadolt függvényt.
    /// Hibát dob, amennyiben a megadott elérési úton a fájl nem található.
    /*!
    \return Visszaadja a JSON fájlból beolvasott értékeket egy mapben.
    */
    static const std::map <std::string, std::string> parseJson(const std::string& json/** [in] a JSON fájl elérési útja */);
    /// Egy korábban beolvasott JSON fájl parzolását végző függvény. Működése során meghívja a parseFromString() függvényt.
    /*!
    \return Visszaadja a JSON fájlból beolvasott értékeket egy mapben.
    */
    static const std::map <std::string, std::string> parseJson(std::istream& jsonFile/** [in] a beolvasott JSON fájlt tartalmazó istream */);
};