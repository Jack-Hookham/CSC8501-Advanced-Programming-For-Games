#pragma once

#include "Prisoner.h"

class GangMember : public Prisoner
{
public:
	GangMember();
	GangMember(Prisoner* p);
	GangMember(GangMember* gm);
	GangMember(const std::string& const folderPath);
	~GangMember();

	//Part 2 outcomes
	void outcomeA();
	void outcomeB();
	void outcomeC();

	friend std::ostream& operator<<(std::ostream& os, const GangMember* gm);

};

