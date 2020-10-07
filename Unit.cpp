#include "Unit.h"

Unit* Unit::parseUnit(const std::string& fname) {
	std::ifstream jsonFile;
	jsonFile.open(fname);
	if (!jsonFile.fail())
	{
		Parser p;
		std::map<std::string, std::string> attributes = p.parseJson(jsonFile);
		if (attributes.find("name") != attributes.end() 
			&& attributes.find("hp") != attributes.end() 
			&& attributes.find("dmg") != attributes.end()){
				jsonFile.close();
				return new Unit(attributes["name"], stoi(attributes["hp"]), stoi(attributes["dmg"]));
		}
		else throw "Incorrect attributes in " + fname + "!";
	}
	else throw fname + " does not exist!";
}

void Unit::getHitBy(const Unit *other) {
	if (b_hP - other->getDmg() > 0)
		b_hP -= other->getDmg();
	else b_hP = 0;
}

bool Unit::isDead() const {
	return b_hP == 0;
}