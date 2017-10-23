#pragma once

#include "Game.h"
#include "Gang.h"

class GangGame : public Game
{
public:
	GangGame();
	GangGame(Gang* a, Gang* b);
	~GangGame();
};

