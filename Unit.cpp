#include "Unit.h"
#include <cmath>
#include <fstream>
#include <map>

void Unit::levelup(){
	while (b_xp >= 100){		
		b_maxHp = round((b_maxHp*1.1));
		b_hP = b_maxHp;
		b_dmg *= 1.1;
		b_xp -= 100;
		b_level++;
		b_acd *= 0.9;
	}
}

void Unit::getHitBy(Unit* other) {
	if (b_hP - other->getDamage() > 0) {
		other->b_xp += other->getDamage();
		b_hP -= other->getDamage();
	}
	else { 
		other->b_xp += b_hP;
		b_hP = 0;
	}
	other->levelup();
}

bool Unit::isAlive() const {
	return b_hP > 0;
}
