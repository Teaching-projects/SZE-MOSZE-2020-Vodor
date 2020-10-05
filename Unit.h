#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Unit
{
private:
	const std::string b_name;
	int b_hP;
	const int b_dmg;
	const double b_acd;
	void getHitBy(const Unit *other);
	int getDmg() const { return b_dmg; }
	double getAcd() const { return b_acd; } 
	int getHP() const { return b_hP; }
	std::string getName() const { return b_name; }
	bool isDead() const;
	friend class Game;
protected:
	void fight(Unit *other);
	Unit(const std::string& name, int hP, int dmg, double acd) : b_name(name), b_hP(hP), b_dmg(dmg), b_acd(acd) {}
	static Unit* parseUnit(const std::string& fname);
};