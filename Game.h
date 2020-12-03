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
#include "Renderer.h"
#include <string>
#include <list>
#include <algorithm>

class Renderer;

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
private:
    Map gameMap; ///< A játéktér.
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
    /// Ez a függvény kirajzolja a játékteret.
    void printMap();
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
    /// Ez a függvény elindítja a játékot.
    void run();

    std::pair<int,int> const getHeroCoords(){ return std::make_pair(hero.x, hero.y); }

    std::list<std::pair<int,int>> const getMonsterCoords();

    Map const getMap(){ return gameMap; }

    friend class Renderer;

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



/*!
 * \class PreparedGame
 * 
 * \brief PreparedGame class
 * 
 * Az előkészített játékért felelős osztály.
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

class PreparedGame : private Game{
private:
    std::list<Renderer*> renderers; //LISTA A RENDEREK TÁROLÁSÁRA
    MarkedMap gameMap; ///< A játéktér.
public:
    /// PreparedGame konstruktor
    PreparedGame(const std::string& filename /** [in] a fájl elérési útvonala*/);
    using Game::run; //ezt majd innen kivehetjük
    //void run(); EZ KELLENI FOG, HOGY KÜLÖN RUNJA LEGYEN A PREPAREDGAMENEK, AMIBEN AZ ÖSSZES RENDERRE LEFUT A TÉMA CPP-BEN NÉZD MEG MI TÖRTÉNIK EBBEN!!!!
    void registerRenderer(Renderer* renderer){
        renderers.push_back(renderer);
    }
};
#endif