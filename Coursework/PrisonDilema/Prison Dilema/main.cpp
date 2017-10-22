#pragma once

#include <iostream>
#include <filesystem>

#include "prisoner.h"
#include "Interpreter.h"
#include "StrategyGenerator.h"
#include "IPDPTournament.h"

int main()
{
	StrategyGenerator::generate(10);

	//Prisoner* prisoner1 = new Prisoner("../Strategies/Test/TestStrategy1.txt");
	//prisoner1->printStrategy();
	//std::cout << "\n";

	//Prisoner* prisoner2 = new Prisoner("../Strategies/Test/TestStrategy2.txt");
	//prisoner2->printStrategy();
	//std::cout << "\n";

	std::vector<std::string> tournamentStrategies;
	for (int i = 0; i < 10; i++)
	{
		std::ostringstream ossPath;
		ossPath << "../Strategies/Generated/Strategy" << i + 1 << ".txt";
		tournamentStrategies.push_back(ossPath.str());
	}

	IPDPTournament* tournament = new IPDPTournament(tournamentStrategies);
	tournament->play();
	tournament->printResults();

	delete tournament;

	//delete prisoner1;
	//delete prisoner2;

	std::cout << "\n";

	std::cin.ignore();
	std::cin.get();

	return 0;
}