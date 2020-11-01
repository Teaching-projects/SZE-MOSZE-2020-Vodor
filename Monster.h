#ifndef MONSTER_H
#define MONSTER_H

#include "Unit.h"
#include "Hero.h"
class Monster : public Unit{
public:
    Monster(std::string name, int hp, int dmg, double acd) : Unit(name, hp, dmg, acd){}
    /// Ez a függvény a .json file parse-olja. 
	static Monster parse(const std::string& fname/** [in] elérési út */);
    void getHitBy(Hero* other);
};

#endif