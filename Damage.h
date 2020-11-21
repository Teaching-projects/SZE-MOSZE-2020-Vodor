#ifndef DAMAGE_H
#define DAMAGE_H

struct Damage
	{
		int physical; ///< A karakter támadási ereje.
		int magical; ///< A karakter mágikus támadási ereje.

        Damage& operator+(const Damage& other){
            Damage dmgToReturn;
            dmgToReturn.physical = this->physical + other.physical;
            dmgToReturn.magical = this->magical + other.magical;
            
            return dmgToReturn;
        }

        Damage& operator+=(const Damage& other){
            this->physical += other.physical;
            this->magical += other.magical;
            return *this;
        }

        Damage& operator*=(const Damage& other){
            this->physical *= other.physical;
            this->magical *= other.magical;
            return *this;
        }

	};

#endif