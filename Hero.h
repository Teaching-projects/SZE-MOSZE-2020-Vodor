#ifndef HERO_H
#define HERO_H

#include "Unit.h"

class Hero : public Unit{
private:
    int b_maxHp; ///< Karakter maximális életereje.
	int b_xp; ///< Karakter fejlődési pont.
	int b_level; ///< Karakter szintje.
    int b_experience_per_level;
    int b_health_point_bonus_per_level;
    int b_damage_bonus_per_level;
    double b_cooldown_multiplier_per_level;

public:
    /// A fight függvény levezényli a csatát és a végén kiírja a győztest. 
	void fightTilDeath(Unit other /** [in] ellenfél karakter */); //ide mégis hero kellene a unit helyett
    Hero(const std::string& name, int hP, int dmg, double acd,
    int experience_per_level,
    int health_point_bonus_per_level,
    int damage_bonus_per_level,
    double cooldown_multiplier_per_level) : Unit(name, hP, dmg, acd),
    b_maxHp(hP), b_xp(0), b_level(1), 
    b_experience_per_level(experience_per_level),
    b_health_point_bonus_per_level(health_point_bonus_per_level),
    b_damage_bonus_per_level(damage_bonus_per_level),
    b_cooldown_multiplier_per_level(cooldown_multiplier_per_level) {} 

    static Hero parse(const std::string& fname/** [in] elérési út */);   
    /// Ez a függvény visszaadja a karakter szintjét.
	int getLevel() const { return b_level; }
    /// Ez a függvény visszaadja a karakter maximális életerejét.
	int getMaxHealthPoints() const {return b_maxHp; }
    void addXp(int amount) { b_xp += amount; }
    /// Ez a függvény ellenőrzi/végzi a szintlépést.
	void levelup();
    void getHitBy(Unit* other);
};

#endif