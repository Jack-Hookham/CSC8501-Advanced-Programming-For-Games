#pragma once

#include "Prisoner.h"

class Gang
{
public:
	Gang();
	~Gang();

private:
	Prisoner* mPrisoners[5];
};

