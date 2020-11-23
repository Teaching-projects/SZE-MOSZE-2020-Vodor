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

class Game{
private:
    Map gameMap;
    std::list<MonsterCoords> monsters;
    Hero hero;
    int heroX;
    int heroY;
public:
    Game();
    Game(const std::string& mapFileName) : gameMap(Map(mapFileName)){}
    void setMap(Map map);
    void putHero(Hero hero, int x, int y);
    void putMonster(Monster monster, int x, int y);
    
    void print();
    void run();

    class OccupiedException : public std::runtime_error{
        OccupiedException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };

    class AlreadyHasHeroException : public std::runtime_error{
        AlreadyHasHeroException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };

    class AlreadyHasUnitException : public std::runtime_error{
        AlreadyHasUnitException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };

    class NotInitializedException : public std::runtime_error{
        NotInitializedException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };

    class GameAlreadyStartedException : public std::runtime_error{
        GameAlreadyStartedException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };
};
#endif