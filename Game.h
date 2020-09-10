#pragma once
#include "Unit.h"
#include <iostream>
#include <vector>

class Game
{
private:
    int round;
    bool winner;
    vector<Unit*> units;
    Unit *att, *def;
    void setAttacker();
    void showStats() const;
    void initVector(int argc, char** argv);
public:
    Game(int argc, char** argv) : round(1), winner(false) { initVector(argc, argv); }
    ~Game();
    void runGame();
};

