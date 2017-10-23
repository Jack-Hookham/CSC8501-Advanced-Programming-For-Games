#pragma once

#include "IPDPGame.h"
#include "StrategyGenerator.h"

class IPDPTournament
{
public:
	IPDPTournament(const int id, const std::vector<std::string>& strategies);
	~IPDPTournament();

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