#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Monster.h"
#include "Hero.h"
#include "Renderer.h"
#include <string>
#include <list>
#include <map>
#include <ostream>

class Renderer;

/*!
 * \struct MonsterCoords
 * 
 * \brief MonsterCoords struct
 * 
 * Ellenfelet tartalmazó struct.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 5.0
 * 
 * \date 2020/12/06 16:30
 * 
 * Created on 2020/12/06 16:30
 */

struct MonsterCoords{ 
    Monster monster;  ///< Ellenfelet tartalmazó változó.
    int x; ///< Ellenfél x koordinátája.
    int y; ///< Ellenfél y koordinátája.
};

/*!
 * \struct b_Hero
 * 
 * \brief b_Hero struct
 * 
 * Hőst tartalmazó struct.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 5.0
 * 
 * \date 2020/12/06 16:30
 * 
 * Created on 2020/12/06 16:30
 */

struct b_Hero{ 
    Hero* hero; ///< Hőst tartalmazó változó.
    int x; ///< Hős x koordinátája.
    int y; ///< Hős y koordinátája.
    /// b_Hero alapértelmezett konstruktor 
    b_Hero() : hero(nullptr), x(-1), y(-1){}
};

/*!
 * \struct printItem
 * 
 * \brief printItem struct
 * 
 * A kirajzoláshoz szükséges segéd karaktereket tartalmazó struct.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 5.0
 * 
 * \date 2020/12/06 16:30
 * 
 * Created on 2020/12/06 16:30
 */

struct printItem{
    const std::string TOP_LEFT = "\u2554"; ///< Bal felső elem a pálya keretéhez.
    const std::string TOP_RIGHT = "\u2557"; ///< Jobb felső elem a pálya keretéhez.
    const std::string BOTTOM_LEFT = "\u255A"; ///< Bal alsó elem a pálya keretéhez.
    const std::string BOTTOM_RIGHT = "\u255D"; ///< Jobb alsó elem a pálya keretéhez.
    const std::string HORIZONTAL = "\u2550\u2550"; ///< Vízszintes elem a pálya keretéhez.
    const std::string VERTICAL =  "\u2551"; ///< Függőleges elem a pálya keretéhez.
    const std::string FREE = "\u2591\u2591"; ///< Szabad elem a pályán.
    const std::string WALL = "\u2588\u2588"; ///< Fal elem a pályán.
    const std::string SINGLEMONSTER = "M\u2591"; ///< Monster elem (1 db).
    const std::string MULTIPLEMONSTERS = "MM"; ///< Monster elem (2 db).
    const std::string HERO = "\u2523\u252B"; ///< Hero elem.
};

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
    /// Game alapértelmezett konstruktor 
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
    explicit Game(const std::string& mapFileName) : gameMap(Map(mapFileName)), mapsetready(true), gamestarted(false),heroready(false){
        textures["free_texture"] = "textures/free.png";
        textures["wall_tecture"] = "textures/wall.png";
    }
    /// Game dekonstruktor
    ~Game(){ delete hero.hero; }
    /// Ez a függvény beállítja a játékteret.
    void setMap(const Map& map);
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

    /*!
    * \class OccupiedException
    * 
    * \brief OccupiedException class
    * 
    * A OccupiedException kivételosztály. 
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
    class OccupiedException : public std::runtime_error{ 
        public:
        /// OccupiedException konstruktor
        explicit OccupiedException(const std::string& errMsg/** [in] hiba üzenet*/) : std::runtime_error(errMsg){}
    };

    /*!
    * \class AlreadyHasHeroException
    * 
    * \brief AlreadyHasHeroException class
    * 
    * A AlreadyHasHeroException kivételosztály. 
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
    class AlreadyHasHeroException : public std::runtime_error{
        public:
        /// AlreadyHasHeroException konstruktor
        explicit AlreadyHasHeroException(const std::string& errMsg/** [in] hiba üzenet*/) : std::runtime_error(errMsg){}
    };

    /*!
    * \class AlreadyHasUnitsException
    * 
    * \brief AlreadyHasUnitsException class
    * 
    * A AlreadyHasUnitsException kivételosztály. 
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
    class AlreadyHasUnitsException : public std::runtime_error{
        public:
        /// AlreadyHasUnitsException konstruktor
        explicit AlreadyHasUnitsException(const std::string& errMsg/** [in] hiba üzenet*/) : std::runtime_error(errMsg){}
    };

    /*!
    * \class NotInitializedException
    * 
    * \brief NotInitializedException class
    * 
    * A NotInitializedException kivételosztály. 
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
    class NotInitializedException : public std::runtime_error{
        public:
        /// NotInitializedException konstruktor
        explicit NotInitializedException(const std::string& errMsg/** [in] hiba üzenet*/) : std::runtime_error(errMsg){}
    };

    /*!
    * \class GameAlreadyStartedException
    * 
    * \brief GameAlreadyStartedException class
    * 
    * A GameAlreadyStartedException kivételosztály. 
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
    class GameAlreadyStartedException : public std::runtime_error{
        public:
        /// GameAlreadyStartedException konstruktor
        explicit GameAlreadyStartedException(const std::string& errMsg/** [in] hiba üzenet*/) : std::runtime_error(errMsg){}
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
    explicit PreparedGame(const std::string& filename /** [in] a fájl elérési útvonala*/);
    using Game::run; 
    using Game::registerRenderer;
};
#endif