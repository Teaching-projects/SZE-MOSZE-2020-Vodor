#include "Unit.h"

Unit* Unit::parseUnit(const std::string& fname){
	std::string name;
	int hp, dmg;
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
				dmg = std::stoi(sbstr);
			}
		}
	    file.close();
        return new Unit(name,hp, dmg);
    }
}

void Unit::levelup(){
	while (b_xp >= 100){		
		b_maxHp *= 1.1;
		b_hP = b_maxHp;
		b_dmg = round((b_dmg*1.1));
		b_xp -= 100;
		b_level++;
	}
}

void Unit::getHitBy(Unit *other) {
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

bool Unit::isDead() const {
	return b_hP == 0;
}