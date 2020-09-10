#include "Game.h"

void Game::setAttacker() {
    if (round % 2 == 0) {
        att = units.at(1);
        def = units.at(0);
    }
    else {
        att = units.at(0);
        def = units.at(1);
    }
    cout << att->getName() << " -> " << def->getName() << endl;
}

void Game::showStats() const {
    for (auto u : units)
        cout << u->getName() << ": HP: " << u->getHP() << ", DMG: " << u->getDmg() << endl;
}

void Game::initVector(int argc, char** argv) {
    for (int i = 1; i < argc; i+=3)
        units.push_back(new Unit(argv[i], stoi(argv[i + 1]), stoi(argv[i + 2])));
}

void Game::runGame() {
    showStats();
    while (!winner) {
        setAttacker();
        def->takeDmg(att->getDmg());
        showStats();
        if (def->isDead()) {
            winner = true;
            cout << def->getName() << " died. " << att->getName() << " wins.";
        }
        else
            round++;
    }
}

Game::~Game() {
    for (auto i : units)
        delete i;
}