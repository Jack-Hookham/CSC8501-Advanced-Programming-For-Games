#pragma once

#include <iostream>

#include "prisoner.h"
#include "Interpreter.h"
#include "StrategyGenerator.h"
#include "TIPDPGame.h"

int main()
{
	//StrategyGenerator::generate(10);

	Prisoner* prisoner1 = new Prisoner("TestStrategy1", "../Strategies/Test/");
	prisoner1->printStrategy();
	std::cout << "\n";

	Prisoner* prisoner2 = new Prisoner("TestStrategy2", "../Strategies/Test/");
	prisoner2->printStrategy();
	std::cout << "\n";

	//PUT GAMES IN TOURNAMENT
	//The Iterated Prisoners Dilemma Problem Game between two prisoners, a and b
	TIPDPGame* game = new TIPDPGame(prisoner1, prisoner2);
	game->play(200);

	delete game;
	delete prisoner1;
	delete prisoner2;

	std::cout << "\n";

	std::cin.ignore();
	std::cin.get();

	return 0;
}