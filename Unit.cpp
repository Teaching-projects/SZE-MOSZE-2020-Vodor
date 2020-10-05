#include "Unit.h"

Unit* Unit::parseUnit(const std::string& fname){
	std::string name;
	int hp, dmg;
	double acd;
	std::ifstream file;  
	file.open(fname);
    if (file.fail()) throw fname + " does not exist.";
    else
    {
		std::string line, sbstr;
		std::string parseS = " : ";
		while (std::getline(file, line)){
			if (line.find("name") != std::string::npos){
				name = line.substr(line.find(parseS)+1);
				name = name.substr(name.find('"')+1,name.find_last_of('"')-3);
			}
			else if (line.find("hp") != std::string::npos){
				sbstr = line.substr(line.find(parseS)+3);
				hp = std::stoi(sbstr.substr(0,sbstr.find(",")));
			}
			else if (line.find("dmg") != std::string::npos){
				sbstr = line.substr(line.find(parseS)+3);
				dmg = std::stoi(sbstr.substr(0,sbstr.find(",")));
			}
			else if (line.find("attackcooldown") != std::string::npos)
			{
				sbstr = line.substr(line.find(parseS)+3);
				acd = std::stod(sbstr);
			}
			
		}
	    file.close();
        return new Unit(name,hp, dmg, acd);
    }
}

void Unit::getHitBy(const Unit *other) {
	if (b_hP - other->getDmg() > 0)
		b_hP -= other->getDmg();
	else b_hP = 0;
}

bool Unit::isDead() const {
	return b_hP == 0;
}