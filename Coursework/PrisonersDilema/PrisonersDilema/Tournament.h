#pragma once

#include "Game.h"
#include "StrategyGenerator.h"

class Tournament
{
public:
	Tournament();
	Tournament(const int id, const std::vector<std::string>& strategies, const int gameIterations = 200, const int tournamentIterations = 1);
	~Tournament();

	void play();
	void generateResults();
	void printResults();

private:
	int mID;
	int mNumStrategies;
	int mGameIterations;
	int mTournamentIterations;
	std::vector<Prisoner*> mPrisoners;

	//Store the formatted tournament results in a string
	std::string mTournamentResults;
	const std::string resultsPath = "../TournamentResults/Prisoner/";

	//Formatting
	const std::string lineBreak = "_______________________________________________________________________________________________________________________\n";
};