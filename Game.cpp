#include "Game.h"

void Game::runGame() {
    winner = u1->fight(u2);
    std::cout << winner->getName() << " wins." << " Remaining hp: "<< winner->getHP()<<".";
}

Game::~Game(){
    delete u1;
    delete u2;
    delete winner;
}