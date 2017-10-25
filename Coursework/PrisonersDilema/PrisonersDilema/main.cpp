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
	std::cout << "2 - Gang Tournament\n";
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

void playTournament(const int total)
{
	std::cout << "How many strategies would you like to generate? ";
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

	Tournament* t = new Tournament(total, tournamentStrategies, gameIterations, tournamentIterations);
	t->play();
	t->generateResults();

	//Hardcoded testing
	//std::vector<std::string> testStrategies;
	//testStrategies.push_back("../Strategies/Test/Strategy8.txt");
	//testStrategies.push_back("../Strategies/Test/Strategy8.txt");
	//tournament = new Tournament(2, testStrategies);
	//tournament->play(gameIterations, tournamentIterations);
	//tournament->generateResults();

	delete t;

	std::cout << "\n";
}

void playGangTournament(const int total)
{
	std::cout << "How many strategies would you like to generate? ";
	int numStrategies;
	numStrategies = getInt();

	std::cout << "How many gangs would you like to generate from these strategies? ";
	int numGangs;
	numGangs = getInt();

	std::cout << "How many iterations per game? ";
	int gameIterations;
	gameIterations = getInt();

	std::cout << "How many times should each gang play each other? ";
	int tournamentIterations;
	tournamentIterations = getInt();

	std::cout << "How often should a spy appear per game?\n";
	std::cout << "0 - 0%\n";
	std::cout << "1 - 5%\n";
	std::cout << "2 - 10%\n";
	std::cout << "3 - 15%\n";
	std::cout << "4 - 20%\n";

	int spyChance = -1;

	while (true)
	{
		switch (getInt())
		{
		case 0:
			spyChance = 0;
			break;
		case 1:
			spyChance = 5;
			break;
		case 2:
			spyChance = 10;
			break;
		case 3:
			spyChance = 15;
			break;
		case 4:
			spyChance = 20;
			break;
		default:
			std::cout << "Not an option\n";
			break;
		}
		if (spyChance != -1)
		{
			break;
		}
	}

	StrategyGenerator::generate(numStrategies, true, 10);

	std::vector<std::string> tournamentStrategies;
	for (int i = 0; i < numStrategies; i++)
	{
		std::ostringstream ossPath;
		ossPath << "../Strategies/Generated/Gang/Strategy" << i + 1 << ".txt";
		tournamentStrategies.push_back(ossPath.str());
	}

	GangTournament* gt = new GangTournament(total, tournamentStrategies, gameIterations, tournamentIterations, numGangs, spyChance);
	gt->play();
	gt->generateResults();

	delete gt;

	std::cout << "\n";
}

int main()
{
	//Gang test
	//int numGangStrats = 10;
	//StrategyGenerator::generate(numGangStrats, true, 10);

	//std::vector<std::string> gangTournamentStrategies;
	//for (int i = 0; i < numGangStrats; i++)
	//{
	//	std::ostringstream ossPath;
	//	ossPath << "../Strategies/Generated/Gang/Strategy" << i + 1 << ".txt";
	//	gangTournamentStrategies.push_back(ossPath.str());
	//}

	//GangTournament* gangTournament = new GangTournament(1, gangTournamentStrategies, 50, 1, 3);
	//gangTournament->play();
	//gangTournament->generateResults();
	//delete gangTournament;

	//Hardcoded testing
	//std::vector<std::string> teststrategies;
	//teststrategies.push_back("../strategies/test/strategy1.txt");
	//teststrategies.push_back("../strategies/test/strategy2.txt");
	//teststrategies.push_back("../strategies/test/strategy3.txt");
	//teststrategies.push_back("../strategies/test/strategy4.txt");
	//teststrategies.push_back("../strategies/test/strategy5.txt");
	//teststrategies.push_back("../strategies/test/strategy6.txt");
	//teststrategies.push_back("../strategies/test/strategy7.txt");
	//teststrategies.push_back("../strategies/test/strategy8.txt");
	//teststrategies.push_back("../strategies/test/strategy9.txt");
	//teststrategies.push_back("../strategies/test/strategy10.txt");
	//Tournament* tournament = new Tournament(2, teststrategies, 200, 1);
	//tournament->play();
	//tournament->generateResults();
	//delete tournament;

	//Count the number of tournaments played of each type - used for tournament ID
	int totalTournaments = 0;
	int totalGangTournaments = 0;
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
			totalTournaments++;
			system("cls");
			playTournament(totalTournaments);
			break;
		case 2:
			totalGangTournaments++;
			system("cls");
			playGangTournament(totalGangTournaments);
			break;
		default:
			std::cout << "Not an option\n";
			break;
		}
	}

	return 0;
}