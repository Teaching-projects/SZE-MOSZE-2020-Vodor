#ifndef REND_H
#define REND_H

#include "Game.h"

class Renderer{
public:
    virtual void render(const Game&) const = 0;
};

#endif