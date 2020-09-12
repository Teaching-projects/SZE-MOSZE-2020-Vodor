#include <string>

class Unit
{
private:
	const std::string b_name;
	int b_hP;
	const int b_dmg;
	friend class Game;
protected:
	void takeDmg(int d);
	int getHP() const { return b_hP; }
	std::string getName() const { return b_name; }
	int getDmg() const { return b_dmg; }
	bool isDead() const;
public:
	Unit(const std::string& name, int hP, int dmg) : b_name(name), b_hP(hP), b_dmg(dmg) {}
};

