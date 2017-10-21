#pragma once

#include <iostream>

#include "prisoner.h"
#include "Interpreter.h"
#include "StrategyGenerator.h"
#include "TIPDPGame.h"

int main()
{
	//StrategyGenerator::generate(10);

	Prisoner* a = new Prisoner("../Strategies/Test/TestStrategy1.txt");
	a->print();
	std::cout << "\n";

	Prisoner* b = new Prisoner("../Strategies/Test/TestStrategy2.txt");
	b->print();
	std::cout << "\n";

	//PUT GAMES IN TOURNAMENT
	//The Iterated Prisoners Dilemma Problem Game between two prisoners, a and b
	TIPDPGame* game = new TIPDPGame(a, b);
	game->play(5);

	delete game;
	delete a;
	delete b;

	std::cout << "\n";

	std::cin.ignore();
	std::cin.get();

	return 0;
}