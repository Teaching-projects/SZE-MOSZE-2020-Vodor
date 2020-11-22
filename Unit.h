#ifndef UNIT_H
#define UNIT_H

/*!
 * \class Unit
 * 
 * \brief Unit class
 * 
 * A Unit karakterért felelős osztály.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 4.0
 * 
 * \date 2020/11/02 13:22
 * 
 * Created on 2020/11/02 13:22
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
	Unit(const std::string& name, int hP, int dmg, double acd, int defense) : b_name(name), b_hP(hP), b_dmg(dmg), b_acd(acd), b_defense(defense) {}
	/// Ez a függvény visszaadja a karakter életerejét.
	int getHealthPoints() const { return b_hP; }
	/// Ez a függvény visszaadja a karakter nevét.
	std::string getName() const { return b_name; }
	/// Ez a függvény visszaadja a karakter meghalt-e.
	bool isAlive() const;
	/// Ez a függvény visszaadja a karakter támadási erejét.
	int getDamage() const { return b_dmg; }
	/// Ez a függvény visszaadja a karakter támadási idejét.
	double getAttackCoolDown() const { return b_acd; } 

protected:
	const std::string b_name;  ///< A karakter neve. 
	int b_hP; ///< A karakter életereje.
	int b_dmg; ///< A karakter támadási ereje.
	double b_acd; ///< Karakter támadási ideje.
	int b_defense;
};

#endif
