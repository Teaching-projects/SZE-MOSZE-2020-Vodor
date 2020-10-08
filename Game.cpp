#include "Game.h"

void Game::runGame() {
    while (!u1->isDead() && !u2->isDead()) {
        u2->getHitBy(u1);
        if (u2->isDead()) 
            std::cout << u1->getName() << " wins." << " Remaining hp: "<< u1->getHP()<<". XP: "<<u1->getXp()<<". Level: "<<u1->getLevel()<<".";
        else {
            u1->getHitBy(u2);
            if (u1->isDead())
                std::cout << u2->getName() << " wins." << " Remaining hp: "<< u2->getHP() <<". XP: "<<u2->getXp()<<". Level: "<<u2->getLevel()<<".";    
        }
    }
}

Game::~Game(){
    delete u1, u2;
}