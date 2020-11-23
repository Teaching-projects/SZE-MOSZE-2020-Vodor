#include "Game.h"

void Game::setMap(Map map){
    if(heros.size() == 0 && monsters.size() == 0){
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

}

void Game::run(){

}

void Game::print(){
    
}