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
 * \version 5.0
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
#include <map>
#include <ostream>

class Renderer;

struct MonsterCoords{   //dox
    Monster monster;
    int x;
    int y;
};

struct b_Hero{//dox
    Hero* hero;
    int x;
    int y;
    b_Hero() : hero(nullptr), x(-1), y(-1){}
};

struct printItem//dox
{
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
};

class Game{
private:
    Map gameMap; ///< A játéktér.
protected:
    bool mapsetready; ///< A játéktér betöltését jelző változó.
    bool gamestarted; ///< A játék indulását jelző változó.
    bool heroready;  ///< A hős betöltését jelző változó.
    std::list<MonsterCoords> monsters;  ///< Az ellenfelek listája.
    b_Hero hero; ///< Hős változó
    /// Ez a függvény ellenőrzi a lépést.
    bool checkIfMoveIsValid(const std::string& direction);
    /// Ez a függvény lép egyet a hőssel.
    void moveHero(const std::string& direction);

    std::map<std::string, std::string> textures; ///< A texturák listája.

    std::list<Renderer*> renderers; ///< A renderek listája.
public:
    /// Game default konstruktor 
    Game(): gameMap(Map()), mapsetready(false), gamestarted(false),heroready(false){
        textures["free_texture"] = "textures/free.png";
        textures["wall_tecture"] = "textures/wall.png";
    }
    /*! \brief Game konstruktor
 	*         
 	*  
 	*  Beállítja a játékot a paramér alapján.
 	*  
 	*  \param mapFileName [in] jatéktér elérése .
 	*/
    Game(const std::string& mapFileName) : gameMap(Map(mapFileName)), mapsetready(true), gamestarted(false),heroready(false){
        textures["free_texture"] = "textures/free.png";
        textures["wall_tecture"] = "textures/wall.png";
    }
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
    /// Ez a függvény új renderelési eljárást add hozzá.
    void registerRenderer(Renderer* renderer) { renderers.push_back(renderer); }
    /// Ez a függvény visszaadja a Hőst.     
    b_Hero getHero() const { return hero; }
    /// Ez a függvény visszaadja az ellenfeleket.
    std::list<MonsterCoords> getMonsters() const { return monsters; }
    /// Ez a függvény visszaadja a játékteret.
    Map getMap() const { return gameMap; }
    /// Ez a függvény visszaadja a texturákat.
    std::map<std::string, std::string> getTextures() const { return textures;}


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
 * \version 5.0
 * 
 * \date 2020/12/01 15:20
 * 
 * Created on 2020/12/01 15:20
 */

class PreparedGame : private Game{
private:
    MarkedMap gameMap; ///< A játéktér.
public:
    /// PreparedGame konstruktor
    PreparedGame(const std::string& filename /** [in] a fájl elérési útvonala*/);
    using Game::run; 
    using Game::registerRenderer;
};
#endif