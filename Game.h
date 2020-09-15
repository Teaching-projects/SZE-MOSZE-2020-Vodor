#include "Unit.h"
#include <iostream>

class Game
{
private:
    Unit *u1, *u2;
    void showStats() const;
    void initUnits(char** argv);
public:
    Game(char** argv)  { initUnits(argv); }
    ~Game();
    void runGame();
};

