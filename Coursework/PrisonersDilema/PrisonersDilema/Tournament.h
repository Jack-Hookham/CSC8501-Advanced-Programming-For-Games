#pragma once

#include "Game.h"
#include "StrategyGenerator.h"

class Tournament
{
public:
	Tournament();
	Tournament(const int id, const std::vector<std::string>& strategies, const int gameIterations = 200, const int tournamentIterations = 1);
	virtual ~Tournament();

	virtual void play(const int gameDetail);
	virtual void generateResults(const int tournamentDetail);
	virtual inline const std::string getResults() const { return mTournamentResults; }
	inline friend std::ostream& operator<<(std::ostream& os, const Tournament* t) { os << t->getResults() << "\n"; return os; }

protected:
	int mID;
	int mNumStrategies;
	int mGameIterations;
	int mTournamentIterations;

	void generatePrisoners(const std::vector<std::string>& strategies);
	void printTournamentHeading(const int gameDetail);

	std::vector<Prisoner*> mPrisoners;

	//Store the formatted tournament results in a string
	std::string mTournamentResults;
	const std::string resultsPath = "../TournamentResults/Prisoner/";

	//Track the total number of games played
	int mGamesPlayed = 0;

	//Formatting
	const std::string lineBreak = "______________________________________________________________________________________________________________________________________________________________________\n";
private:
};