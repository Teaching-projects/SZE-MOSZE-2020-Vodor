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
 * \version 5.0
 * 
 * \date 2020/11/02 13:22
 * 
 * Created on 2020/11/02 13:22
 */

#include <map>
#include <iterator>
#include <variant>
#include <type_traits>
#include <list>

using jsonData = std::map <std::string, std::variant<std::string, int, double>>;

class JSON
{
private:
	jsonData b_data; ///< Adatoknak létrehozott map.

public:
	typedef std::list<std::variant<std::string, int, double>> list;
    /*! \brief JSON konstruktor
 	*         
 	*  
	*  \param data [in] adat.
 	*/
    JSON(jsonData data) : b_data(data){}
    /// JSON fájlból beolvasott karakterlánc parzolását végző függvény.
    /// Hibát dob, amennyiben hiányos, vagy sérült a fájl. Pl.: hiányoznak kulcsok adott párokból, vagy nincsenek meg a kezdő, és/vagy záró karakterek
    /*!
    	\return Visszaadja a JSON fájlból beolvasott értékeket egy mapben.
    */
    static const JSON parseFromString(std::string inputString /** [in] JSON formátumú karakterlánc */);
    /// Egy fájl elérési útja alapján parzoló függvény. Működése során meghívja a istream-et váró overloadolt függvényt.
    /// Hibát dob, amennyiben a megadott elérési úton a fájl nem található.
    /*!
    	\return Visszaadja a JSON fájlból beolvasott értékeket egy mapben.
    */
    static const JSON parseFromFile(const std::string& json/** [in] a JSON fájl elérési útja */);
    /// Egy korábban beolvasott JSON fájl parzolását végző függvény. Működése során meghívja a parseFromString() függvényt.
    /*!
    	\return Visszaadja a JSON fájlból beolvasott értékeket egy mapben.
   	*/
    static const JSON parseJson(std::istream& jsonFile/** [in] a beolvasott JSON fájlt tartalmazó istream */);
    /// Ez a függvény vizsgálja adott key benne van-e mapben.
    const int count(const std::string& key/** [in] kulcs*/);
    /// Ez a függvény visszaad egy listát a key alapján.
	///Hibát dob, amennyiben az adott kulcs nincs a mapben.
	template <typename T> 
	inline typename std::enable_if<std::is_same<T, JSON::list>::value, T>::type 
	get(const std::string& key){
		if (!count(key)) throw ParseException("Key does not exist in map!");
		else{
				list toReturn;
				std::istringstream elements(std::get<std::string>(b_data[key]));
				std::copy(std::istream_iterator<std::string>(elements),
               		std::istream_iterator<std::string>(),
           	 		std::back_inserter(toReturn));

				return toReturn;
			}
		}

	/// Ez a függvény visszaad egy valuet a key alapján.
	///Hibát dob, amennyiben az adott kulcs nincs a mapben.
	template <typename T> inline typename std::enable_if<!std::is_same<T, JSON::list>::value, T>::type
	get(const std::string& key/** [in] kulcs*/){
       	if (!count(key)) throw ParseException("Key does not exist in map!");
        else return std::get<T>(b_data[key]);
    }

    class ParseException : public std::runtime_error{
    public:
       	/*! \brief ParseException konstruktor
 		*         
 		*  
		*  \param data [in] hibaüzenet.
 		*/
       	ParseException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };
};

#endif