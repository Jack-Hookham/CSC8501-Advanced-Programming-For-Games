#pragma once

#include "Tournament.h"
#include "Gang.h"
#include "GangGame.h"

class GangTournament : public Tournament
{
public:
	GangTournament();
	GangTournament(const int id, const std::vector<std::string>& strategies, const bool leaderChoice, const int gameIterations = 200, 
		const int tournamentIterations = 1, const int numGangs = 2, const int spyChance = 0);
	~GangTournament();

	inline const std::string getResults() const { return mTournamentResults; }
	inline friend std::ostream& operator<<(std::ostream& os, const GangTournament* gt) { os << gt->getResults() << "\n"; return os; }

	void play(const int gameDetail);
	const std::string generateResults(const int tournamentDetail);

	inline void setSpyChance(const int value) { mSpyChance = value; }
	inline void setLeaderChange(const bool value) { mLeaderChange = value; }

private:
	std::vector<Gang*> mGangs;
	int mSpyChance;
	//Does the leader change their choice
	//true - yes
	//false - no
	bool mLeaderChange;

	//Print the strategies of each gang
	void printGangs();

	//Store the formatted tournament results in a string
	std::string mTournamentResults;
	const std::string resultsPath = "../TournamentResults/Gang/";

	void printTournamentHeading(const int gameDetail);
};
