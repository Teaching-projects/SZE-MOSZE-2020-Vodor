#include "Game.h"

/*
	Szechenyi Istvan Egyetem - MOSZE 2020 - Vodor
		- Borbely Roland
		- Vitez Marcell
		- Voznek Peter
*/

int main(int argc, char** argv)
{
	if (argc == 3)
		try
		{
			Game g(argv);
			g.runGame();
		}
		catch(std::string e)
		{
			std::cout << e;
		}
	else
		std::cout << "Incorrect number of parameters!";
}

