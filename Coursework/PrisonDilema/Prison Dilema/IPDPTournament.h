#pragma once

#include "IPDPGame.h"
#include "StrategyGenerator.h"

class IPDPTournament
{
public:
	IPDPTournament(const std::vector<std::string>& strategies);
	~IPDPTournament();

	void play();
	void printResults();

private:
	std::vector<Prisoner*> mPrisoners;

	//Formatting
	const std::string lineBreak = "__________________________________________________________________________________________________________________________\n";
};