#include "Game.h"

void Game::setMap(Map map){    
    if(heros.empty() && monsters.empty()){
        gameMap = map;
        mapsetready = true;
    }
    else 
        throw AlreadyHasUnitsException("Game already has Units.");
}

void Game::putHero(Hero hero, int x, int y){
    if(heros.size()>1)
    {
        throw AlreadyHasHeroException("Game already has Hero.");
    }
    else
    {
        if(mapsetready){
            if(gameMap.get(x,y) == gameMap.Free){
                HeroCoord onehero = {hero,x,y};
                heros.push_back(onehero);
            }
            else
                throw OccupiedException("Coordinate occupied");
        }
        else 
            throw Map::WrongIndexException("Map not set");
    }
    
}

void Game::putMonster(Monster monster, int x, int y){
    if(mapsetready){
        if(gameMap.get(x,y) == gameMap.Free){
            MonsterCoords onemonster = {monster,x,y};
            monsters.push_back(onemonster);
        }
        else
            throw OccupiedException("Coordinate occupied");
    }
    else 
        throw Map::WrongIndexException("Map not set");

}

void Game::run(){

}

void Game::printMap(){
    std::cout<<"╔";

    for (int i = 0; i < gameMap.getMaxLength(); i++)
        std::cout<<"═";

    std::cout<<"╗"<<std::endl;

    for (int y = 0; y < gameMap.getMapSize(); y++){
        std::cout<<"║";

        for (int x = 0; x < gameMap.getRowLength(y); x++){
            if (gameMap.get(x, y) == gameMap.Free)std::cout<<"░";
            else std::cout<<"█";  
        }

        if(gameMap.getRowLength(y)<gameMap.getMaxLength())
            for (int i = 0; i < (gameMap.getMaxLength()-gameMap.getRowLength(y)); i++)
                std::cout<<"█";

        std::cout<<"║"<<std::endl;
    }

    std::cout<<"╚";

    for (int i = 0; i < gameMap.getMaxLength(); i++)
        std::cout<<"═";

    std::cout<<"╝"<<std::endl;
}