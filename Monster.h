#ifndef MONSTER_H
#define MONSTER_H

#include "Unit.h"
#include "Hero.h"
#include <string>

/*!
 * \class Monster
 * 
 * \brief Monster class
 * 
 * A Szörnyekért felelős osztály.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 5.0
 * 
 * \date 2020/11/02 13:22
 * 
 * Created on 2020/11/02 13:22
 */

class Hero;

class Monster : public Unit{
public:

	/*! \brief Monster konstruktor
 	*         
 	*  
 	*  Beállítja a Szörny adatait a paraméterek alapján.
 	*  
 	*  \param name [in] Szörny neve
	*  \param hp [in] Szörny életereje
	*  \param dmg [in] Szörny támadási ereje
	*  \param acd [in] Szörny támadási ideje
	*  \param defense [in] Szörny védelme
	*  \param texture [in] Szörny textúrája
 	*/
   	Monster(const std::string& name, int hp, Damage dmg, double acd, int defense, const std::string& texture) : Unit(name, hp, dmg, acd, defense, texture){}
    /// Ez a függvény parse-olja a megadott JSON formátumú fájlt. 
	static Monster parse(const std::string& fname/** [in] elérési út */);
    /// Ez a függvény megüti a Szörnyet.
    void getHitBy(Hero* other/** [in] ellenfél karakter */);
};

#endif
