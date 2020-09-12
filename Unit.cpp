#include "Unit.h"

void Unit::takeDmg(int d) {
	if (b_hP - d > 0)
		b_hP -= d;
	else b_hP = 0;
}

bool Unit::isDead() const {
	return b_hP == 0;
}

