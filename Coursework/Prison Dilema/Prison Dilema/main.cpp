#pragma once

#include <iostream>

#include "Prisoner.h"
#include "Interpreter.h"
#include "StrategyGenerator.h"


int main()
{
	Prisoner a("../Strategies/TestStrategy1.txt");
	a.print();

	StrategyGenerator::generate(10);

	cin.ignore();
	cin.get();

	return 0;
}