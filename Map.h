#ifndef MAP_H
#define MAP_H


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
 * \version 4.0
 * 
 * \date 2020/11/17 18:39
 * 
 * Created on 2020/11/17 18:39
 */

#include <vector>
#include <string>
#include <fstream>


class Map{
protected:
    std::vector<std::string> map; ///< A játék térképe.
public:
    int getMapSize() { return map.size();}
    int getRowWidth(int y) {return map[y].length(); }
    int getMaxLength();

    /// Enum a térkép elemeinek.
    enum type{
        Free, ///< járható út 
        Wall ///< fal
        };
    Map(){}
    /// Map konstruktor, beolvas egy térképet egy adott fájlból.
    Map(const std::string& filename /** [in] a fájl elérési útvonala*/);
    

    /// Függvény, ami visszaadja az adott koordinátán milyen elem szerepel a térképen.
    /*!
        \param x [in] x koordináta
        \param y [in] y koordináta
        \return Járható út, vagy fal.
    */
    Map::type get(unsigned int x, unsigned int y) const;

    class WrongIndexException : public std::runtime_error{
    public:
        WrongIndexException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };
};


class MarkedMap : public Map
{
    public:
    ///A MarkedMap konstruktura beolvas egy térképet egy adott fájból amiben előre megtalálhatóak a Hős (H) és a szörnyek (1-2-3) pozíciói
    MarkedMap(const std::string& filename /** [in] a fájl elérési útvonala*/);
    MarkedMap(){}
   
    std::pair<int,int> getHeroPosition() const; ///Visszaadja a Hero (H) poziciojat
    std::vector<std::pair<int,int>> getMonsterPositions(char c) const; ///Visszaadja a Monster (1-2-3) poziciojat
};

#endif