#pragma once

#include <iostream>

#include "Prisoner.h"
#include "Interpreter.h"
#include "StrategyGenerator.h"

int main()
{
	StrategyGenerator::generate(10);

	Prisoner a("../Strategies/WriteTest9.txt");
	a.print();

	std::cout << "\n";

	std::cin.ignore();
	std::cin.get();

	return 0;
}