#pragma once

#include <iostream>
#include <filesystem>

#include "prisoner.h"
#include "Interpreter.h"
#include "StrategyGenerator.h"
#include "Tournament.h"

int main()
{
	const int tournamentSize = 10;
	StrategyGenerator::generate(tournamentSize, true);

	std::vector<std::string> tournamentStrategies;
	for (int i = 0; i < 10; i++)
	{
		std::ostringstream ossPath;
		ossPath << "../Strategies/Generated/Prisoner/Strategy" << i + 1 << ".txt";
		tournamentStrategies.push_back(ossPath.str());
	}

	Tournament* tournament = new Tournament(1, tournamentStrategies);
	tournament->play();
	tournament->generateResults();

	delete tournament;

	std::cout << "\n";

	std::cin.ignore();
	std::cin.get();

	return 0;
}