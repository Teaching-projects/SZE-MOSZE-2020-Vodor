#include "Game.h"

void Game::setMap(Map map){
    gameMap = map;
}

void Game::putHero(Hero hero, int x, int y){

}

void Game::putMonster(Monster monster, int x, int y){

}

void Game::run(){

}

void Game::printMap(){
/*
        ╔════════════════════════════════════════╗
        ║████████████████████████████████████████║
        ║██░░░░░░░░MM░░░░░░░░░░░░░░M░░░████M░████║
        ║██░░M░░░░░████████MM░░██████████░░MM████║
        ║██░░░░░░M░██████████MM░░████░░░░░░MM████║
        ║██░░┣┫░░░░████████████MM░░░░MM██████████║
        ║████████████████████████████████████████║
        ╚════════════════════════════════════════╝
*/
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