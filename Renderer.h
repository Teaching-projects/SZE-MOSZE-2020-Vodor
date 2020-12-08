#ifndef REND_H
#define REND_H

#include "Game.h"
class Game;

/*!
 * \class Renderer
 * 
 * \brief Renderer abstract class
 * 
 * Absztrakt osztály, példányosítani nem lehet, konstruktora sincs.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 5.0
 * 
 * \date 2020/12/03 21:37
 * 
 * Created on 2020/12/03 21:37
 */

class Renderer{
public:
    /// Render függvény
    virtual void render(const Game&/**[in] a kiírandó Game*/) const = 0;
};

#endif