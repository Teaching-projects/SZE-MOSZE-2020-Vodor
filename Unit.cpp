#include "Unit.h"

Unit* Unit::parseUnit(const std::string& fname) {
	Parser p;
	std::map<std::string, std::string> attributes = p.parseJson(fname);
	if (attributes.find("name") != attributes.end() && 
		attributes.find("hp") != attributes.end() &&
		attributes.find("dmg") != attributes.end() &&
		attributes.find("attackcooldown") != attributes.end()) 
			return new Unit(attributes["name"], stoi(attributes["hp"]), stoi(attributes["dmg"]), stod(attributes["attackcooldown"]));
	else throw "Incorrect attributes in " + fname + "!";
}

void Unit::getHitBy(const Unit *other) {
	if (b_hP - other->getDmg() > 0)
		b_hP -= other->getDmg();
	else b_hP = 0;
}

bool Unit::isDead() const {
	return b_hP == 0;
}

Unit* Unit::fight(Unit *other) {
	if(this->isDead())	return other;
	if(other->isDead())	return this;

	other->getHitBy(this);
	if(other->isDead())
		return this;

	this->getHitBy(other);
    if (this->isDead())
    	return other;

	double acdthis = this->getAcd();
	double acdother = other->getAcd();
	Unit* last = other;

	while(!this->isDead() && !other->isDead())
	{
		if(acdthis == acdother)
		{
			if (last == this)
			{
				other->getHitBy(this);
				if(!other->isDead())
					this->getHitBy(other);
				acdthis = this->getAcd();
				acdother = other->getAcd();
				last = other;
			}
			else
			{
				this->getHitBy(other);
				if(!this->isDead())
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
	return last;
}