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
	std::vector <std::string> keysNeeded {"experience_per_level","health_point_bonus_per_level", "damage_bonus_per_level",
							 "cooldown_multiplier_per_level","name", "base_health_points", "base_damage", "base_attack_cooldown"};
	JSON returnedJSON = JSON::parseFromFile(fname);
    	bool okay = true;
    	for (auto key : keysNeeded)
        	if(!returnedJSON.count(key))
			okay = false;
    
	if (okay) 
	    return Hero(returnedJSON.get<std::string>("name"), 
			stoi(returnedJSON.get<std::string>("base_health_points")),
			stoi(returnedJSON.get<std::string>("base_damage")),
			stod(returnedJSON.get<std::string>("base_attack_cooldown")),
			stoi(returnedJSON.get<std::string>("experience_per_level")),
			stoi(returnedJSON.get<std::string>("health_point_bonus_per_level")),
			stoi(returnedJSON.get<std::string>("damage_bonus_per_level")),
			stod(returnedJSON.get<std::string>("cooldown_multiplier_per_level")));
	else throw JSON::ParseException("Incorrect attributes in " + fname + "!");
}

void Hero::levelup(){
	while (b_xp >= b_experience_per_level){		
		b_maxHp += b_health_point_bonus_per_level;
		b_hP = b_maxHp;
		b_dmg += b_damage_bonus_per_level;
		b_xp -= b_experience_per_level;
		b_level++;
		b_acd *= b_cooldown_multiplier_per_level;
	}
}

void Hero::getHitBy(Unit* other){
	if (b_hP - other->getDamage() > 0) {
		b_hP -= other->getDamage();
	}
	else { 
		b_hP = 0;
	}
}
