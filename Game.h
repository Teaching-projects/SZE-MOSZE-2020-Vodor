/*!
 * \class Game
 * 
 * \brief Game class
 * 
 * Ez az osztály a Csata lefutását vezényeli le.
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 3.2
 * 
 * \date 2020/10/15 17:05
 * 
 * Created on 2020/10/15 17:05
 */

#include "Unit.h"

class Game
{
private:
    Unit *u1, *u2;
public:
    /*! \brief Game konstruktor
    *         
    *  
    *  Beállítja a karakterek adatait a paraméterek alapján.
    *  
    *  \param argv [in] karaktertípusú tömb az argumentumokkal  
    */
    Game(char** argv) : u1(Unit::parseUnit(argv[1])), u2(Unit::parseUnit(argv[2])) { }
    /// Game osztály destruktora.
    ~Game();
    /// A runGame függvény lefuttatja a csatát.
    void runGame();
};