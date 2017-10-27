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
	std::cout << "3 - Question Analysis\n";
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
	std::cout << "How many strategies would you like to generate?\n(Entering 0 will load 10 already generated strategies)\n";
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

	bool generate;
	if (numStrategies > 0)
	{
		generate = true;
		StrategyGenerator::generate(numStrategies, false, 10);
	}
	else
	{
		generate = false;
		numStrategies = 10;
	}

	std::vector<std::string> tournamentStrategies;
	for (int i = 0; i < numStrategies; i++)
	{
		std::ostringstream ossPath;
		if (generate)
		{
			ossPath << "../Strategies/Generated/Prisoner/Strategy" << i + 1 << ".txt";
		}
		else
		{
			ossPath << "../Strategies/Test/Prisoner/Strategy" << i + 1 << ".txt";
		}
		tournamentStrategies.push_back(ossPath.str());
	}

	Tournament* t = new Tournament(total, tournamentStrategies, gameIterations, tournamentIterations);
	t->play(gameDetail);
	std::cout << t->generateResults(tournamentDetail);

	delete t;

	std::cout << "\n";
}

void playGangTournament(const int total)
{
	std::cout << "How many strategies would you like to generate?\n(Entering 0 will load 10 already generated strategies)\n";
	int numStrategies;
	numStrategies = getInt();

	std::cout << "How many gang combinations would you like to generate from these strategies? ";
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
	std::cout << "5 - Custom Value\n";

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
		case 5:
			while (spyChance < 0 || spyChance > 100)
			{
				std::cout << "Enter value (0 - 100): ";
				spyChance = getInt();
				if (spyChance > 100) { std::cout << "Value must be less than 100\n"; }
				else if (spyChance < 0) { std::cout << "Value must be greater than 0\n"; }
			}
			break;
		default:
			std::cout << "Not an option\n";
			break;
		}
	}

	bool leaderChange = false;
	if (spyChance > 0)
	{
		std::cout << "\nShould the leader change their choice after a member is revealed as not the spy?\n";
		std::cout << "0 - No\n";
		std::cout << "1 - Yes\n";

		int lc = -1;
		while (lc < 0)
		{
			switch (getInt())
			{
			case 0:
				lc = 0;
				leaderChange = false;
				break;
			case 1:
				lc = 1;
				leaderChange = true;
				break;
			default:
				std::cout << "Not an option\n";
				break;
			}
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

	bool generate;
	if (numStrategies > 0)
	{
		generate = true;
		StrategyGenerator::generate(numStrategies, true, 10);
	}
	else
	{
		generate = false;
		numStrategies = 10;
	}

	std::vector<std::string> tournamentStrategies;
	for (int i = 0; i < numStrategies; i++)
	{
		std::ostringstream ossPath;
		if (generate)
		{
			ossPath << "../Strategies/Generated/Gang/Strategy" << i + 1 << ".txt";
		}
		else
		{
			ossPath << "../Strategies/Test/Gang/Strategy" << i + 1 << ".txt";
		}
		tournamentStrategies.push_back(ossPath.str());
	}

	GangTournament* gt = new GangTournament(total, tournamentStrategies, leaderChange, gameIterations, tournamentIterations, numGangs, spyChance);
	gt->play(gameDetail);
	std::cout << gt->generateResults(tournamentDetail);

	delete gt;

	std::cout << "\n";
}

void questionAnalysis(const int total)
{
	std::cout << "1) Determine the best gang based combination of strategies when no spy is present\n";
	std::cout << "2) Given the best strategy, when a spy is present, is it better for the gang leader to change their choice?\n";
	std::cout << "Enter to continue...\n";

	std::cin.ignore();
	std::cin.get();
	//Answer Questions
	int numGangStrats = 10;
	StrategyGenerator::generate(numGangStrats, true, 10);

	std::vector<std::string> gangTournamentStrategies;
	for (int i = 0; i < numGangStrats; i++)
	{
		std::ostringstream ossPath;
		ossPath << "../Strategies/Generated/Gang/Strategy" << i + 1 << ".txt";
		gangTournamentStrategies.push_back(ossPath.str());
	}

	std::cout << "Running Tournaments...\n";
	std::ostringstream ossOut;
	//Run a tournament with 0 spy chance then run the same tournament with the same gang combinations
	GangTournament* gangTournament = new GangTournament(total, gangTournamentStrategies, false, 50, 1, 20, 0);
	gangTournament->play(0);
	ossOut << gangTournament->generateResults(2);

	gangTournament->setSpyChance(5);
	gangTournament->setLeaderChange(true);
	gangTournament->play(0);
	ossOut << gangTournament->generateResults(2);

	gangTournament->setSpyChance(5);
	gangTournament->setLeaderChange(false);
	gangTournament->play(0);
	ossOut << gangTournament->generateResults(2);

	gangTournament->setSpyChance(10);
	gangTournament->setLeaderChange(true);
	gangTournament->play(0);
	ossOut << gangTournament->generateResults(2);

	gangTournament->setSpyChance(10);
	gangTournament->setLeaderChange(false);
	gangTournament->play(0);
	ossOut << gangTournament->generateResults(2);

	gangTournament->setSpyChance(15);
	gangTournament->setLeaderChange(true);
	gangTournament->play(0);
	ossOut << gangTournament->generateResults(2);

	gangTournament->setSpyChance(15);
	gangTournament->setLeaderChange(false);
	gangTournament->play(0);
	ossOut << gangTournament->generateResults(2);

	gangTournament->setSpyChance(20);
	gangTournament->setLeaderChange(true);
	gangTournament->play(0);
	ossOut << gangTournament->generateResults(2);

	gangTournament->setSpyChance(20);
	gangTournament->setLeaderChange(false);
	gangTournament->play(0);
	ossOut << gangTournament->generateResults(2);

	//Write results to file and print
	FileManager::writeToFile("../TournamentResults/Gang/Questions.txt", ossOut.str());
	std::cout << ossOut.str();

	delete gangTournament;
}

int main()
{
	//Test infinite loop
	//Prisoner* p = new Prisoner("../Strategies/Test/Prisoner/Loop.txt");
	//Interpreter::interpretDecision(p);
	//delete p;

	//Count the number of tournaments played of each type - used for tournament ID
	int totalTournaments = 0;
	int totalGangTournaments = 0;

	//Set console dimensions
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1550, 900, TRUE);

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
		case 3:
			totalGangTournaments++;
			system("cls");
			questionAnalysis(totalGangTournaments);
			break;
		default:
			std::cout << "Not an option\n";
			break;
		}
	}

	return 0;
}