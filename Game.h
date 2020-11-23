#ifndef GAME_H
#define GAME_H
#include "Map.h"
#include "Monster.h"
#include "Hero.h"
#include <string>
#include <list>

struct MonsterCoords{
    Monster monster;
    int x;
    int y;
};

struct HeroCoord{
    Hero hero;
    int x;
    int y;
};

class Game{
private:
    Map gameMap;
    std::list<MonsterCoords> monsters;
    std::list<HeroCoord> heros;
public:
    Game();
    Game(const std::string& mapFileName) : gameMap(Map(mapFileName)){}
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

    class AlreadyHasUnitException : public std::runtime_error{
        public:
        AlreadyHasUnitException(const std::string& errMsg) : std::runtime_error(errMsg){}
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