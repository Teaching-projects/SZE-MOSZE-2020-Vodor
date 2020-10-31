/*!
 * \class Hero
 * 
 * \brief Hero class
 * 
 * A Hero karakterért felelős osztály.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 3.2
 * 
 * \date 2020/10/15 17:05
 * 
 * Created on 2020/10/15 17:05
 */


#include <string>
#include "JSON.h"

class Unit
{
public:

	/*! \brief Unit konstruktor
 	*         
 	*  
 	*  Beállítja a karakterek adatait a paraméterek alapján.
 	*  
 	*  \param name [in] karakter neve
	*  \param hp [in] karakter életereje
	*  \param dmg [in] karakter támadási ereje
	*  \param acd [in] karakter támadási ideje
 	*/
	Unit(const std::string& name, int hP, int dmg, double acd) : b_name(name), b_hP(hP), b_dmg(dmg), b_acd(acd), b_maxHp(hP), b_xp(0), b_level(1) {}
	/// Ez a függvény a .json file parse-olja. 
	static Unit parse(const std::string& fname/** [in] elérési út */);
	/// Ez a függvény visszaadja a karakter életerejét.
	int getHealthPoints() const { return b_hP; }
	/// Ez a függvény visszaadja a karakter maximális életerejét.
	int getMaxHealthPoints() const {return b_maxHp; }
	/// Ez a függvény visszaadja a karakter nevét.
	std::string getName() const { return b_name; }
	/// Ez a függvény visszaadja a karakter meghalt-e.
	bool isAlive() const;
	/// Ez a függvény visszaadja a karakter szintjét.
	int getLevel() const { return b_level; }

	/// Ez a függvény ellenőrzi/végzi a szintlépést.
	void levelup();
	/// Ez a függvény sebzést oszt ki a karakterre.
	void getHitBy(Unit *other /** [in] ellenfél karakter */ );
	/// Ez a függvény visszaadja a karakter támadási erejét.
	int getDamage() const { return b_dmg; }
	/// Ez a függvény visszaadja a karakter támadási idejét.
	double getAttackCoolDown() const { return b_acd; } 

protected:
	const std::string b_name;  ///< A karakter neve. 
	int b_hP; ///< A karakter életereje.
	int b_dmg; ///< A karakter támadási ereje.
	double b_acd; ///< Karakter támadási ideje.
	int b_maxHp; ///< Karakter maximális életereje.
	int b_xp; ///< Karakter fejlődési pont.
	int b_level; ///< Karakter szintje.
};