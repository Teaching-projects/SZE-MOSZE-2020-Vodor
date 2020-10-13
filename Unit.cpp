#include "Unit.h"

Unit* Unit::parseUnit(const std::string& fname) {
	Parser p;
	std::map<std::string, std::string> attributes = p.parseJson(fname);
	if (attributes.find("name") != attributes.end() && 
		attributes.find("hp") != attributes.end() &&
		attributes.find("dmg") != attributes.end())
			return new Unit(attributes["name"], stoi(attributes["hp"]), stoi(attributes["dmg"]));
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