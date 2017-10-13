#pragma once

#include <iostream>

#include "Prisoner.h"
#include "Interpreter.h"


int main()
{
	Prisoner a("../Strategies/TestStrategy1.txt");
	a.print();

	cin.ignore();
	cin.get();

	return 0;
}