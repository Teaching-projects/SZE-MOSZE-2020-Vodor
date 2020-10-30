#include "Game.h"
#include <iostream>

void Game::runGame() {
    std::cout << u1->fight(u2)->getName() << " wins." << " Remaining hp: "<< u1->fight(u2)->getHp()<<".";
}

Game::~Game(){
    delete u1;
    delete u2;
}