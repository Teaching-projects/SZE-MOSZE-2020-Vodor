#include "Game.h"

void Game::showStats() const {
    std::cout << u1->getName() << ": HP: " << u1->getHP() << ", DMG: " << u1->getDmg() << std::endl;
    std::cout << u2->getName() << ": HP: " << u2->getHP() << ", DMG: " << u2->getDmg() << std::endl;
}

void Game::initUnits(char** argv)
{
      u1 = new Unit(argv[1], std::stoi(argv[2]), std::stoi(argv[3]));
      u2 = new Unit(argv[4], std::stoi(argv[5]), std::stoi(argv[6]));
}

void Game::runGame() {
    showStats();
    while (!u1->isDead() && !u2->isDead()) {
        std::cout << u1->getName() << " -> " << u2->getName() << std::endl;
        u2->getHitBy(u1);
        showStats();
        if (u2->isDead()) 
            std::cout << u2->getName() << " died. " << u1->getName() << " wins.";
        else
        {
            std::cout << u2->getName() << " -> " << u1->getName() << std::endl;
            u1->getHitBy(u2);
            showStats();
            if (u1->isDead())
                std::cout << u1->getName() << " died. " << u2->getName() << " wins.";    
        }
    }
}

Game::~Game() {
    delete u1, u2;
}