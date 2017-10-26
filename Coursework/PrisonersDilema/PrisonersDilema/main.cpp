#pragma once

#include <iostream>
#include <filesystem>
#include <windows.h>

#include "prisoner.h"
#include "Interpreter.h"
#include "StrategyGenerator.h"
#include "Tournament.h"
#include "GangTournament.h"

#undef max

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

	std::cout << "\nDetail for game stats?\n";
	std::cout << "0 - None\n";
	std::cout << "1 - Simple\n";
	std::cout << "2 - Detailed\n";

	int gameDetail = -1;

	while (gameDetail < 0)
	{
		gameDetail = getInt();
		if (gameDetail < 0 || gameDetail > 2)
		{
			gameDetail = -1;
			std::cout << "Not an option\n";
		}
		else
		{
			break;
		}
	}	

	std::cout << "\nDetail for tournament stats?\n";
	std::cout << "0 - None\n";
	std::cout << "1 - Simple\n";
	std::cout << "2 - Detailed\n";

	int tournamentDetail = -1;

	while (tournamentDetail < 0)
	{
		tournamentDetail = getInt();
		if (tournamentDetail < 0 || tournamentDetail > 2)
		{
			tournamentDetail = -1;
			std::cout << "Not an option\n";
		}
		else
		{
			break;
		}
	}

	StrategyGenerator::generate(numStrategies, false, 10);

	std::vector<std::string> tournamentStrategies;
	for (int i = 0; i < numStrategies; i++)
	{
		std::ostringstream ossPath;
		ossPath << "../Strategies/Generated/Prisoner/Strategy" << i + 1 << ".txt";
		tournamentStrategies.push_back(ossPath.str());
	}

	Tournament* t = new Tournament(total, tournamentStrategies, gameIterations, tournamentIterations);
	t->play(gameDetail);
	t->generateResults(tournamentDetail);

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

	while (spyChance < 0)
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
	}

	std::cout << "\nDetail for game stats?\n";
	std::cout << "0 - None\n";
	std::cout << "1 - Simple\n";
	std::cout << "2 - Detailed\n";

	int gameDetail = -1;

	while (gameDetail < 0)
	{
		gameDetail = getInt();
		if (gameDetail < 0 || gameDetail > 2)
		{
			gameDetail = -1;
			std::cout << "Not an option\n";
		}
		else
		{
			break;
		}
	}

	std::cout << "\nDetail for tournament stats?\n";
	std::cout << "0 - None\n";
	std::cout << "1 - Simple\n";
	std::cout << "2 - Detailed\n";

	int tournamentDetail = -1;

	while (tournamentDetail < 0)
	{
		tournamentDetail = getInt();
		if (tournamentDetail < 0 || tournamentDetail > 2)
		{
			tournamentDetail = -1;
			std::cout << "Not an option\n";
		}
		else
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
	gt->play(gameDetail);
	gt->generateResults(tournamentDetail);

	delete gt;

	std::cout << "\n";
}

int main()
{
	//Set console dimensions
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1280, 900, TRUE);

	//Gang test
	int numGangStrats = 10;
	//StrategyGenerator::generate(numGangStrats, true, 10);

	std::vector<std::string> gangTournamentStrategies;
	//for (int i = 0; i < numGangStrats; i++)
	//{
	//	std::ostringstream ossPath;
	//	ossPath << "../Strategies/Test/Strategy" << i + 1 << ".txt";
	//	gangTournamentStrategies.push_back(ossPath.str());
	//}
	std::vector<std::string> testGangStrategies;
	testGangStrategies.push_back("../strategies/test/Silence.txt");
	testGangStrategies.push_back("../strategies/test/Silence.txt");
	testGangStrategies.push_back("../strategies/test/Silence.txt");
	testGangStrategies.push_back("../strategies/test/Silence.txt");
	testGangStrategies.push_back("../strategies/test/Silence.txt");
	testGangStrategies.push_back("../strategies/test/Betray.txt");
	testGangStrategies.push_back("../strategies/test/Betray.txt");
	testGangStrategies.push_back("../strategies/test/Silence.txt");
	testGangStrategies.push_back("../strategies/test/Silence.txt");
	testGangStrategies.push_back("../strategies/test/Silence.txt");

	GangTournament* gangTournament = new GangTournament(1, testGangStrategies, 50, 1, 10, 20);
	gangTournament->play(2);
	gangTournament->generateResults(2);
	delete gangTournament;


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