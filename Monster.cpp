#include "Monster.h"

Monster Monster::parse(const std::string& fname) {
	JSON returnedJSON = JSON::parseFromFile(fname);

	if (returnedJSON.checkIfKeyExists("name") &&
		returnedJSON.checkIfKeyExists("health_points") &&
		returnedJSON.checkIfKeyExists("damage") &&
		returnedJSON.checkIfKeyExists("attack_cooldown")) 
			return Monster(returnedJSON.get<std::string>("name"), 
					stoi(returnedJSON.get<std::string>("health_points")),
					stoi(returnedJSON.get<std::string>("damage")),
					stod(returnedJSON.get<std::string>("attack_cooldown")));
	else throw "Incorrect attributes in " + fname + "!";
}