#pragma once

#include "Tournament.h"
#include "Gang.h"

class GangTournament : public Tournament
{
public:
	GangTournament();
	GangTournament(const int id, const std::vector<std::string>& strategies, const int gameIterations = 200, const int tournamentIterations = 1, const int numGangs = 2);
	~GangTournament();

	void play();
	void generateResults();

private:
	std::vector<Gang*> mGangs;

	//Store the formatted tournament results in a string
	std::string mTournamentResults;
	const std::string resultsPath = "../TournamentResults/Gang/";
};

