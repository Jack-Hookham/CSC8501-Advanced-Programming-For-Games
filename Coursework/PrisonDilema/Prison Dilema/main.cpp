#pragma once

#include <iostream>
#include <filesystem>

#include "prisoner.h"
#include "Interpreter.h"
#include "StrategyGenerator.h"
#include "IPDPTournament.h"

int main()
{
	//StrategyGenerator::generate(10);

	Prisoner* prisoner1 = new Prisoner("../Strategies/Test/TestStrategy1.txt");
	prisoner1->printStrategy();
	std::cout << "\n";

	Prisoner* prisoner2 = new Prisoner("../Strategies/Test/TestStrategy2.txt");
	prisoner2->printStrategy();
	std::cout << "\n";

	//PUT GAMES IN TOURNAMENT
	std::vector<std::string> strategies;

	for (int i = 1; i <= 10; i++)
	{
		
	}

	IPDPTournament* tournament = new IPDPTournament(strategies);

	//The Iterated Prisoners Dilemma Problem Game between two prisoners, a and b
	IPDPGame* game = new IPDPGame(prisoner1, prisoner2);
	game->play(200);

	delete tournament;
	delete game;
	delete prisoner1;
	delete prisoner2;

	std::cout << "\n";

	std::cin.ignore();
	std::cin.get();

	return 0;
}