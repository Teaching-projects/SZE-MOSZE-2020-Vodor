#include "Unit.h"

Unit* Unit::parseUnit(const std::string& fname){
	//TODO: pass filename instead of the string that contains the whole file
	Parser p;
	std::ifstream jsonFile;
	jsonFile.open(fname);

    std::map<std::string, std::string> attributes = p.parseJson(jsonFile);
	jsonFile.close();

	return new Unit(attributes["name"], stoi(attributes["hp"]), stoi(attributes["dmg"]));
}

void Unit::getHitBy(const Unit *other) {
	if (b_hP - other->getDmg() > 0)
		b_hP -= other->getDmg();
	else b_hP = 0;
}

bool Unit::isDead() const {
	return b_hP == 0;
}