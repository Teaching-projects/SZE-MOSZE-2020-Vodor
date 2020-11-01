#include "Hero.h"
#include <vector>

void Hero::fightTilDeath(Unit other) {
	other.getHitBy(this);
	double acdthis = this->getAttackCoolDown();
	double acdother = other.getAttackCoolDown();
	bool lastthis = true; 

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
							 "cooldown_multiplier_per_level","name", "healh_points", "damage", "attack_cooldown"};
	JSON returnedJSON = JSON::parseFromFile(fname);
    	bool okay = true;
    	for (auto key : keysNeeded)
        	if(!returnedJSON.checkIfKeyExists(key))
			okay = false;
    
	if (okay) 
	    return Hero(returnedJSON.get<std::string>("name"), 
			stoi(returnedJSON.get<std::string>("health_points")),
			stoi(returnedJSON.get<std::string>("damage")),
			stod(returnedJSON.get<std::string>("attack_cooldown")),
			stoi(returnedJSON.get<std::string>("experience_per_level")),
			stoi(returnedJSON.get<std::string>("health_point_bonus_per_level")),
			stoi(returnedJSON.get<std::string>("damage_bonus_per_level")),
			stod(returnedJSON.get<std::string>("cooldown_multiplier_per_level")));
	else throw "Incorrect attributes in " + fname + "!";
}
