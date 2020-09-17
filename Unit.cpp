#include "Unit.h"

Unit* Unit::parseUnit(const std::string& fname){
	std::vector<std::string> data;
	std::ifstream file;  
	file.open(fname);
    if (file.fail()) throw fname + " does not exist.";
    else
    {
		std::string line;
		std::string parseS = " : ";
		while (std::getline(file, line))
			if (line != "}" && line != "{") 
            {
			    line.erase(0, line.find(parseS) + parseS.length() + 1);
				if (line.find('"') != std::string::npos)
					line.erase(line.find('"'), line.length());
				else
					line.erase(line.find(","), line.length());               
				data.push_back(line);
			}	
			
	    file.close();
        return new Unit(data[0], stoi(data[1]), stoi(data[2]));
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