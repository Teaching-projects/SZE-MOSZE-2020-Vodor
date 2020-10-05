#include "Game.h"

void Game::runGame() {
    u1->fight(u2);
}

Game::~Game() {
    delete u1, u2;
}