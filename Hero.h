#ifndef HERO_H
#define HERO_H

#include "Unit.h"
#include "Monster.h"

class Hero : public Unit{
private:
    int b_experience_per_level;
    int b_health_point_bonus_per_level;
    int b_damage_bonus_per_level;
    double b_cooldown_multiplier_per_level;
public:
    /// A fight függvény levezényli a csatát és a végén kiírja a győztest. 
	void fightTilDeath(Unit other /** [in] ellenfél karakter */);
    Hero(const std::string& name, int hP, int dmg, double acd,
    int experience_per_level,
    int health_point_bonus_per_level,
    int damage_bonus_per_level,
    double cooldown_multiplier_per_level) : Unit(name, hP, dmg, acd), 
    b_experience_per_level(experience_per_level),
    b_health_point_bonus_per_level(health_point_bonus_per_level),
    b_damage_bonus_per_level(damage_bonus_per_level),
    b_cooldown_multiplier_per_level(cooldown_multiplier_per_level) {} 

    static Hero parse(const std::string& fname/** [in] elérési út */);   
};

#endif