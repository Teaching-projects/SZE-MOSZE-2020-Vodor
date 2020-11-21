#include "Hero.h"
#include <vector>
#include <cmath>

void Hero::fightTilDeath(Monster& other) {
	double acdthis = this->getAttackCoolDown();
	double acdother = other.getAttackCoolDown();
	bool lastthis = false; 

	while(this->isAlive() && other.isAlive())
	{
		if(acdthis == acdother)
		{
			if (lastthis) 
			{
				other.getHitBy(this);
				if(other.isAlive())
					this->getHitBy(&other);
				acdthis = this->getAttackCoolDown();
				acdother = other.getAttackCoolDown();
				lastthis = false;
			}
			else
			{
				this->getHitBy(&other);
				if(this->isAlive())
					other.getHitBy(this);
				acdthis = this->getAttackCoolDown();
				acdother = other.getAttackCoolDown();
				lastthis = true;
			}	
		}
		else if((acdthis - acdother) < 0)
		{
			other.getHitBy(this);
			acdother -= acdthis;
			acdthis = this->getAttackCoolDown();
			lastthis = true;
		}
		else 
		{
			this->getHitBy(&other);
			acdthis -= acdother;
			acdother = other.getAttackCoolDown();
			lastthis = false;
		}		
	}
}

Hero Hero::parse(const std::string& fname) {
	std::vector <std::string> keysNeeded {"experience_per_level","health_point_bonus_per_level", "damage_bonus_per_level"
							 "cooldown_multiplier_per_level","name", "base_health_points", "base_attack_cooldown, magical_damage_bonus_per_level"};
	JSON returnedJSON = JSON::parseFromFile(fname);
    bool okay = true;
    for (auto key : keysNeeded)
       	if(!returnedJSON.count(key))
		okay = false;
	Damage damage;

	if(returnedJSON.count("damage")) damage.physical = returnedJSON.get<int>("damage");
	else damage.physical = 0;
	
	if(returnedJSON.count("magical-damage")) damage.magical = returnedJSON.get<int>("magical-damage");
	else damage.magical = 0;
    
	if (okay) 
	     return Hero(returnedJSON.get<std::string>("name"), 
			returnedJSON.get<int>("base_health_points"),
			damage,
			returnedJSON.get<double>("base_attack_cooldown"),
			returnedJSON.get<int>("experience_per_level"),
			returnedJSON.get<int>("health_point_bonus_per_level"),
			returnedJSON.get<int>("damage_bonus_per_level"),
			returnedJSON.get<int>("magical_damage_bonus_per_level"),
			returnedJSON.get<double>("cooldown_multiplier_per_level"));
	else throw JSON::ParseException("Incorrect attributes in " + fname + "!");
}

void Hero::levelup(){
	while (b_xp >= b_experience_per_level){		
		b_maxHp += b_health_point_bonus_per_level;
		b_hP = b_maxHp;
		b_damage.physical += b_damage_bonus_per_level;
		b_damage.magical += b_magical_damage_bonus_per_level;
		b_xp -= b_experience_per_level;
		b_level++;
		b_acd *= b_cooldown_multiplier_per_level;
	}
}

void Hero::getHitBy(Unit* other){
	if (b_hP - other->getDamage().physical > 0){
		b_hP -= other->getDamage().physical;
		if (b_hP - other->getDamage().magical > 0) 
			b_hP -= other->getDamage().magical;
		else b_hP = 0;
	}
	else b_hP = 0;
}
