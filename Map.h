#ifndef MAP_H
#define MAP_H

#include <vector>
#include <list>
#include <string>
#include <ostream>

/*!
 * \class Map
 * 
 * \brief Map class
 * 
 * A játék térképének eltárolásáért felelős osztály.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 5.0
 * 
 * \date 2020/11/17 18:39
 * 
 * Created on 2020/11/17 18:39
 */

class Map{
protected:
    std::vector<std::string> map; ///< A játék térképe.
public:
    /// Ez a függvény visszaadja a játéktér magasságát.
    int getMapSize() { return map.size();}
    /// Ez a függvény visszaadja a játéktér szélességét az adott sorba.
    int getRowWidth(int y) {return map[y].length(); }
    /// Ez a függvény visszaadja a játéktér max szélességét.
    int getMaxLength();

    /// Enum a térkép elemeinek.
    enum type{
        Free, ///< Járható út.
        Wall ///< Fal.
        };
    
    /// Map alapértelmezett konstruktora. 
    Map(){}
    /// Map konstruktor, beolvas egy térképet egy adott fájlból.
    explicit Map(const std::string& filename /** [in] a fájl elérési útvonala*/);
    
    /// Függvény, ami visszaadja az adott koordinátán milyen elem szerepel a térképen.
    /*!
        \param x [in] x koordináta
        \param y [in] y koordináta
        \return Járható út, vagy fal.
    */
    Map::type get(unsigned int x, unsigned int y) const;

    /*!
    * \class WrongIndexException
    * 
    * \brief WrongIndexException class
    * 
    * A WrongIndexException kivételosztály. 
    * 
    * 
    * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
    * 
    * \version 5.0
    * 
    * \date 2020/11/17 18:39
    * 
    * Created on 2020/11/17 18:39
    */
    class WrongIndexException : public std::runtime_error{
        public:
        /// WrongIndexException konstruktor.
        explicit WrongIndexException(const std::string& errMsg/** [in] hiba üzenet*/) : std::runtime_error(errMsg){}
    };
};

/*!
 * \class MarkedMap
 * 
 * \brief MarkedMap class
 * 
 * A MarkedMap konstruktura beolvas egy térképet egy adott fájból amiben előre megtalálhatóak a Hős és a szörnyek pozíciói.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 5.0
 * 
 * \date 2020/11/17 18:39
 * 
 * Created on 2020/11/17 18:39
 */

class MarkedMap : public Map
{
    public:
    /// MarkedMap konstruktor.
    explicit MarkedMap(const std::string& filename /** [in] a fájl elérési útvonala*/);
    /// MarkedMap default konstruktor.
    MarkedMap(){}
    ///Visszaadja a Hős pozícióját.
    std::pair<int,int> getHeroPosition() const;
    ///Visszaadja a kért Monsterek pozícióját.
    std::list<std::pair<int,int>> getMonsterPositions(char c) const; 
};

#endif