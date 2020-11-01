#include "Monster.h"

Monster Monster::parse(const std::string& fname) {
	std::vector <std::string> keysNeeded {"name", "health_points", "damage", "attack_cooldown"};
	JSON returnedJSON = JSON::parseFromFile(fname);
	bool okay = true;
	for (auto key : keysNeeded)
        if(!returnedJSON.count(key))
			okay = false;

	if (okay) 
	    return Monster(returnedJSON.get<std::string>("name"), 
			stoi(returnedJSON.get<std::string>("health_points")),
			stoi(returnedJSON.get<std::string>("damage")),
			stod(returnedJSON.get<std::string>("attack_cooldown")));
	else throw JSON::ParseException("Incorrect attributes in " + fname + "!");
}