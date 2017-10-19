#pragma once

#include <iostream>

#include "Prisoner.h"
#include "Interpreter.h"
#include "StrategyGenerator.h"
#include "TIPDPGame.h"

int main()
{
	StrategyGenerator::generate(10);

	Prisoner a("../Strategies/TestStrategy1.txt");
	a.print();
	std::cout << "\n";

	Prisoner b("../Strategies/TestStrategy2.txt");
	b.print();

	//The Iterated Prisoners Dilemma Problem Game between two prisoners, a and b
//	TIPDPGame game(a, b);
//	game.play(200);

	std::cout << "\n";

	std::cin.ignore();
	std::cin.get();

	return 0;
}