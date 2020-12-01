#ifndef GAME_H
#define GAME_H

/*!
 * \class Game
 * 
 * \brief Game class
 * 
 * A játékért felelős osztály.
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

#include "Map.h"
#include "Monster.h"
#include "Hero.h"
#include <string>
#include <list>
#include <algorithm>

struct MonsterCoords{
    Monster monster;
    int x;
    int y;
};

struct b_Hero{
    Hero* hero;
    int x;
    int y;
    b_Hero() : hero(nullptr), x(-1), y(-1){}
};

class Game{
protected:
    const std::string TOP_LEFT = "\u2554";
    const std::string TOP_RIGHT = "\u2557";
    const std::string BOTTOM_LEFT = "\u255A";
    const std::string BOTTOM_RIGHT = "\u255D";
    const std::string HORIZONTAL = "\u2550\u2550";
    const std::string VERTICAL =  "\u2551";
    const std::string FREE = "\u2591\u2591";
    const std::string WALL = "\u2588\u2588"; 
    const std::string SINGLEMONSTER = "M\u2591";
    const std::string MULTIPLEMONSTERS = "MM";
    const std::string HERO = "\u2523\u252B";
    Map gameMap; ///< A játéktér.
    bool mapsetready; ///< A játéktér betöltését jelző változó.
    bool gamestarted; ///< A játék indulását jelző változó.
    bool heroready;  ///< A hős betöltését jelző változó.
    std::list<MonsterCoords> monsters;  ///< A ellenfelek listája.
    b_Hero hero; ///< Hős változó
    /// Ez a függvény kiírja az ellenfeleket.
    bool printMonsters(int x, int y); 
    /// Ez a függvény ellenőrzi a lépést.
    bool checkIfMoveIsValid(const std::string& direction);
    /// Ez a függvény lép egyet a hőssel.
    void moveHero(const std::string& direction);
public:
    /// Game default konstruktor 
    Game(): gameMap(Map()), mapsetready(false), gamestarted(false),heroready(false){}
    /*! \brief Game konstruktor
 	*         
 	*  
 	*  Beállítja a játékot a paramér alapján.
 	*  
 	*  \param mapFileName [in] jatéktér elérése .
 	*/
    Game(const std::string& mapFileName) : gameMap(Map(mapFileName)), mapsetready(true), gamestarted(false),heroready(false){}
    /// Game dekonstruktor
    ~Game(){ delete hero.hero; }
    /// Ez a függvény beállítja a játékteret.
    void setMap(Map map);
    /// Ez a függvény hozzáadja a hőst.
    void putHero(Hero hero, int x, int y);
    /// Ez a függvény hozzáad egy ellenfelet.
    void putMonster(Monster monster, int x, int y);
    /// Ez a függvény kirajzolja a játékteret.
    void printMap();
    /// Ez a függvény elindítja.
    void run();

    class OccupiedException : public std::runtime_error{ 
        public:
        OccupiedException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };

    class AlreadyHasHeroException : public std::runtime_error{
        public:
        AlreadyHasHeroException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };

    class AlreadyHasUnitsException : public std::runtime_error{
        public:
        AlreadyHasUnitsException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };

    class NotInitializedException : public std::runtime_error{
        public:
        NotInitializedException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };

    class GameAlreadyStartedException : public std::runtime_error{
        public:
        GameAlreadyStartedException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };
};

class PreparedGame : private Game{
public:
    PreparedGame(const std::string& filename);
    using Game::run;
};
#endif