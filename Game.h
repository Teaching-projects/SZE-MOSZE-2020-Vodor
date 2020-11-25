#ifndef GAME_H
#define GAME_H
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
private:
    Map gameMap;
    bool mapsetready;
    bool gamestarted;
    bool heroready;
    std::list<MonsterCoords> monsters;
    b_Hero hero;
    bool printMonsters(int x, int y);
    bool checkIfMoveIsValid(const std::string& direction);
    void moveHero(const std::string& direction);
public:
    Game(): gameMap(Map()), mapsetready(false), gamestarted(false),heroready(false){}
    Game(const std::string& mapFileName) : gameMap(Map(mapFileName)), mapsetready(true), gamestarted(false),heroready(false){}
    ~Game(){ delete hero.hero; }
    void setMap(Map map);
    void putHero(Hero hero, int x, int y);
    void putMonster(Monster monster, int x, int y);
    
    void printMap();
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
#endif