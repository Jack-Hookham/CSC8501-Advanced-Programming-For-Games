#pragma once

#include "IPDPGame.h"

class IPDPTournament
{
public:
	IPDPTournament(std::vector<std::string> strategies);
	~IPDPTournament();

private:
	std::vector<IPDPGame> games;
};

