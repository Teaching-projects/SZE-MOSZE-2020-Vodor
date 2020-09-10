#include "Unit.h"

void Unit::takeDmg(int d) {
	if (hP - d > 0)
		hP -= d;
	else hP = 0;
}

bool Unit::isDead() {
	if (hP == 0)
		return true;
	else return false;
}

