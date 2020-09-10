#pragma once
#include <string>
using namespace std;

class Unit
{
private:
	const string name;
	int hP;
	const int dmg;
public:
	Unit(const string& n, int h, int d) : name(n), hP(h), dmg(d) {}
	~Unit() { }
	int getHP() const { return hP; }
	string getName() const { return name; }
	int getDmg() const { return dmg; }
	void takeDmg(int d);
	bool isDead();
};

