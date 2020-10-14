#include "Game.h"

void Game::runGame() {
    std::cout << u1->fight(u2)->getName() << " wins." << " Remaining hp: "<< u1->fight(u2)->getHP()<<".";
}

Game::~Game(){
    delete u1;
    delete u2;
}