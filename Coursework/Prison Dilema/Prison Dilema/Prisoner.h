#pragma once

#include <iostream>

#include "FileManager.h"

using namespace std;

class Prisoner
{
public:
	Prisoner(string strategyPath);
	~Prisoner();

	void print();

private:
	const int MAX_LINES = 20;
	string strategyLines[20];
};

