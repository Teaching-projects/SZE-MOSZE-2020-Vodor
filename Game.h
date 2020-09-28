#include "Unit.h"

class Game
{
private:
    Unit *u1, *u2;
public:
    Game(char** argv) : u1(Unit::parseUnit(argv[1])), u2(Unit::parseUnit(argv[2])) { }
    ~Game();
    void runGame();
};