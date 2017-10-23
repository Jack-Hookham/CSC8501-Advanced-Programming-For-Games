#pragma once

#include "Game.h"
#include "StrategyGenerator.h"

class Tournament
{
public:
	Tournament();
	Tournament(const int id, const std::vector<std::string>& strategies);
	~Tournament();

	void play();
	void generateResults();
	void printResults();

private:
	int mID;
	std::vector<Prisoner*> mPrisoners;

	//Store the formatted tournament results in a string
	std::string mTournamentResults;
	const std::string resultsPath = "../TournamentResults/";

	//Formatting
	const std::string lineBreak = "_______________________________________________________________________________________________________________________\n";
};