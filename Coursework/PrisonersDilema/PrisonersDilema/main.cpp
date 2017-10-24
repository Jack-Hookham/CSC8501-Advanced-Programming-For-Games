#pragma once

#include <iostream>
#include <filesystem>

#include "prisoner.h"
#include "Interpreter.h"
#include "StrategyGenerator.h"
#include "Tournament.h"
#include "GangTournament.h"

void printOptions()
{
	std::cout << "What would you like to do?\n";
	std::cout << "0 - Quit\n";
	std::cout << "1 - Tournament\n";
}

int getInt()
{
	int x;
	if (std::cin >> x)
	{
		return x;
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Not an option\n";
		printOptions();
		return getInt();
	}
}

void playTournament()
{
	std::cout << "\nHow many strategies would you like to generate? ";
	int numStrategies;
	numStrategies = getInt();

	std::cout << "How many iterations per game? ";
	int gameIterations;
	gameIterations = getInt();

	std::cout << "How many times should each strategy play each other? ";
	int tournamentIterations;
	tournamentIterations = getInt();

	StrategyGenerator::generate(numStrategies, false, 10);

	std::vector<std::string> tournamentStrategies;
	for (int i = 0; i < numStrategies; i++)
	{
		std::ostringstream ossPath;
		ossPath << "../Strategies/Generated/Prisoner/Strategy" << i + 1 << ".txt";
		tournamentStrategies.push_back(ossPath.str());
	}

	Tournament* tournament = new Tournament(1, tournamentStrategies, gameIterations, tournamentIterations);
	tournament->play();
	tournament->generateResults();

	//Hardcoded testing
	//std::vector<std::string> testStrategies;
	//testStrategies.push_back("../Strategies/Test/Strategy8.txt");
	//testStrategies.push_back("../Strategies/Test/Strategy8.txt");
	//tournament = new Tournament(2, testStrategies);
	//tournament->play(gameIterations, tournamentIterations);
	//tournament->generateResults();

	delete tournament;

	std::cout << "\n";
}

int main()
{
	//Gang test
	int numGangStrats = 10;
	StrategyGenerator::generate(numGangStrats, true, 10);

	std::vector<std::string> gangTournamentStrategies;
	for (int i = 0; i < numGangStrats; i++)
	{
		std::ostringstream ossPath;
		ossPath << "../Strategies/Generated/Gang/Strategy" << i + 1 << ".txt";
		gangTournamentStrategies.push_back(ossPath.str());
	}

	GangTournament* gangTournament = new GangTournament(1, gangTournamentStrategies, 100, 1, 2);
	gangTournament->play();
	gangTournament->generateResults();

	while (true)
	{
		printOptions();

		int choice = getInt();
		switch (choice)
		{
		case 0:
			return 0;
			break;
		case 1:
			playTournament();
			break;
		default:
			std::cout << "Not an option\n";
			break;
		}
	}

	return 0;
}