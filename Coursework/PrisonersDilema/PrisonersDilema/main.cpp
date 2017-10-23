#pragma once

#include <iostream>
#include <filesystem>

#include "prisoner.h"
#include "Interpreter.h"
#include "StrategyGenerator.h"
#include "IPDPTournament.h"

int main()
{
	const int tournamentSize = 10;
	StrategyGenerator::generate(tournamentSize);

	std::vector<std::string> tournamentStrategies;
	for (int i = 0; i < 10; i++)
	{
		std::ostringstream ossPath;
		ossPath << "../Strategies/Generated/Strategy" << i + 1 << ".txt";
		tournamentStrategies.push_back(ossPath.str());
	}

	IPDPTournament* tournament = new IPDPTournament(1, tournamentStrategies);
	tournament->play();
	tournament->generateResults();

	delete tournament;

	std::cout << "\n";

	std::cin.ignore();
	std::cin.get();

	return 0;
}