#pragma once

#include <iostream>

#include "Prisoner.h"
#include "Interpreter.h"
#include "StrategyGenerator.h"

int main()
{
	Prisoner a("../Strategies/TestStrategy1.txt");
	a.print();

	std::cout << "\n";

	StrategyGenerator::generate(10);

	std::cin.ignore();
	std::cin.get();

	return 0;
}