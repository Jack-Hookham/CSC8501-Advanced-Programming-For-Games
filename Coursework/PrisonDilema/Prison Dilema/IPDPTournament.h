#pragma once

#include "IPDPGame.h"

class IPDPTournament
{
public:
	IPDPTournament(std::vector<std::string> strategies);
	~IPDPTournament();

	void play();
	void printResults();

private:
	std::vector<Prisoner*> mPrisoners;
	//std::vector<IPDPGame> games;
};