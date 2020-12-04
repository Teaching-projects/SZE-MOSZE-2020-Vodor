#include "Monster.h"
#include <vector>

Monster Monster::parse(const std::string& fname) {
	std::vector <std::string> keysNeeded {"name", "health_points", "attack_cooldown", "defense"};
	JSON returnedJSON = JSON::parseFromFile(fname);
	bool okay = true;
	for (auto key : keysNeeded)
        	if(!returnedJSON.count(key))
			okay = false;

	Damage damage;
	std::string texture;

	if(returnedJSON.count("damage")) damage.physical = returnedJSON.get<int>("damage");
	else damage.physical = 0;
	
	if(returnedJSON.count("magical-damage")) damage.magical = returnedJSON.get<int>("magical-damage");
	else damage.magical = 0;

	if(returnedJSON.count("texture")) texture = returnedJSON.get<std::string>("texture");
	else texture = "svg/placeholder.svg";

	if (okay) 
	    return Monster(returnedJSON.get<std::string>("name"), 
			returnedJSON.get<int>("health_points"),
			damage,
			returnedJSON.get<double>("attack_cooldown"),
			returnedJSON.get<int>("defense"),
			texture);
	else throw JSON::ParseException("Incorrect attributes in " + fname + "!");
}


void Monster::getHitBy(Hero* other) {
	if(other->getDamage().physical > b_defense){
		if (b_hP - (other->getDamage().physical-b_defense) > 0){
			other->addXp(other->getDamage().physical-b_defense);
			b_hP -= (other->getDamage().physical-b_defense);
			other->levelup();
			if(b_hP - other->getDamage().magical > 0) {
				other->addXp(other->getDamage().magical);
				b_hP -= other->getDamage().magical;
			}
			else {
			other->addXp(b_hP);
			b_hP = 0;
			}
		}
		else {
		other->addXp(b_hP);
		b_hP = 0;
		}
		other->levelup();
	}
	else{
		if(b_hP - other->getDamage().magical > 0) {
			other->addXp(other->getDamage().magical);
			b_hP -= other->getDamage().magical;
		}
		else {
			other->addXp(b_hP);
			b_hP = 0;
		}
		other->levelup();
	}
}
