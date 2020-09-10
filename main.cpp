#include <iostream>
#include "Game.h"

/*
	Szechenyi Istvan Egyetem - MOSZE 2020 - Vodor
		- Borbely Roland
		- Vitez Marcell
		- Voznek Peter
*/

int main(int argc, char** argv)
{
	if (argc == 7)
	{
		Game g(argc, argv);
		g.runGame();
	}
	else
		cout << "Incorrect number of parameters!";
    
}

