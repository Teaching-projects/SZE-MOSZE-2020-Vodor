#ifndef DAMAGE_H
#define DAMAGE_H
#include <iostream>

/*!
 * \struct Damage
 * 
 * \brief Damage struct
 * 
 * A karaktereket sebzését tartalmazó struct.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 5.0
 * 
 * \date 2020/12/06 16:30
 * 
 * Created on 2020/12/06 16:30
 */

struct Damage
{
	int physical; ///< A karakter támadási ereje.
	int magical; ///< A karakter mágikus támadási ereje.
    /// Operátor ami két damaget ad össze.
    Damage operator+(const Damage& other){
        Damage dmgToReturn;
        dmgToReturn.physical = this->physical + other.physical;
        dmgToReturn.magical = this->magical + other.magical;
            
        return dmgToReturn;
    }
    /// Operátor ami egy damagehez hozzáad még egy damaget
    Damage& operator+=(const Damage& other){
        this->physical += other.physical;
        this->magical += other.magical;
        return *this;
    }
    /// Operátor ami egy damaget megszoroz egy másik damage-el
    Damage& operator*=(const Damage& other){
        this->physical *= other.physical;
        this->magical *= other.magical;
        return *this; 
    }
    /// Operátor egy damage kiiratására
    friend std::ostream& operator<<(std::ostream& out, const Damage& dmg){
        out<<"Physical: "<<dmg.physical<<", Magical: "<<dmg.magical;
        return out;
    }
};

#endif