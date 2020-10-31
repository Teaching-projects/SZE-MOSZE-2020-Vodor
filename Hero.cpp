#include "Hero.h"
#include <cmath>
#include <fstream>
#include <map>

Hero Hero::parse(const std::string& fname) {
	JSON returnedJSON = JSON::parseFromFile(fname);

	if (returnedJSON.checkIfKeyExists("name") &&
		returnedJSON.checkIfKeyExists("health_points") &&
		returnedJSON.checkIfKeyExists("damage") &&
		returnedJSON.checkIfKeyExists("attack_cooldown")) 
			return Hero(returnedJSON.get<std::string>("name"), 
					stoi(returnedJSON.get<std::string>("health_points")),
					stoi(returnedJSON.get<std::string>("damage")),
					stod(returnedJSON.get<std::string>("attack_cooldown")));
	else throw "Incorrect attributes in " + fname + "!";
}

void Hero::levelup(){
	while (b_xp >= 100){		
		b_maxHp = round((b_maxHp*1.1));
		b_hP = b_maxHp;
		b_dmg *= 1.1;
		b_xp -= 100;
		b_level++;
		b_acd *= 0.9;
	}
}

void Hero::getHitBy(Monster *other) {
	if (b_hP - other->getDmg() > 0) {
		other->b_xp += other->getDmg();
		b_hP -= other->getDmg();
	}
	else { 
		other->b_xp += b_hP;
		b_hP = 0;
	}
	other->levelup();
}

bool Hero::isAlive() const {
	return b_hP > 0;
}

void Hero::fightTilDeath(Monster *other) {

	other->getHitBy(this);
	double acdthis = this->getAcd();
	double acdother = other->getAcd();
	Hero* last = this;

	while(this->isAlive() && other->isAlive())
	{
		if(acdthis == acdother)
		{
			if (last == this)
			{
				other->getHitBy(this);
				if(other->isAlive())
					this->getHitBy(other);
				acdthis = this->getAcd();
				acdother = other->getAcd();
				last = other;
			}
			else
			{
				this->getHitBy(other);
				if(this->isAlive())
					other->getHitBy(this);
				acdthis = this->getAcd();
				acdother = other->getAcd();
				last = this;
			}	
		}
		else if((acdthis - acdother) < 0)
		{
			other->getHitBy(this);
			acdother -= acdthis;
			acdthis = this->getAcd();
			last = this;
		}
		else 
		{
			this->getHitBy(other);
			acdthis -= acdother;
			acdother = other->getAcd();
			last = other;
		}		
	}
}
