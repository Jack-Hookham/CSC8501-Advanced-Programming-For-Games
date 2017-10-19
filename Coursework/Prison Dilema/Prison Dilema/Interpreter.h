#pragma once

#include <iostream>
#include <vector>

#include "Language.h"
#include "Prisoner.h"

class Interpreter
{
public:
	//Determine a decison (betray/silent) based on the prisoner's strategy
	static int interpretDecision(Prisoner& prisoner);

	//Compare two strategies and determine a result for strategyA
	static int compareStrategies(Prisoner& prisonerA, Prisoner& prisonerB);

private:

};

