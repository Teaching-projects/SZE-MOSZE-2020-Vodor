#include "Unit.h"


bool Unit::isAlive() const {
	return b_hP > 0;
}

void Unit::getHitBy(Unit* other){
	if (b_hP - other->getDamage() > 0) {
		b_hP -= other->getDamage();
	}
	else { 
		b_hP = 0;
	}
}