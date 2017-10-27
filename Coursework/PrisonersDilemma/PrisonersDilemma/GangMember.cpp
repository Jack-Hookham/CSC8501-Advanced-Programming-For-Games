#include "GangMember.h"

GangMember::GangMember()
{
}

GangMember::GangMember(Prisoner* p)
{
	mStrategyName = p->getStrategyName();
	mStrategyPath = p->getStrategyPath();
	mStrategy = p->getStrategy();
	mVariables[PsiLang::varEnums::CUMULATIVE_SCORE + 1] = { 0 };
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::UNKOWN_DECISION;
}

GangMember::GangMember(GangMember* gm)
{
	mStrategyName = gm->getStrategyName();
	mStrategyPath = gm->getStrategyPath();
	mStrategy = gm->getStrategy();
	mVariables[PsiLang::varEnums::CUMULATIVE_SCORE + 1] = { 0 };
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::UNKOWN_DECISION;
	mIsSpy = gm->getSpy();
}

GangMember::~GangMember()
{
}

void GangMember::softReset()
{
	Prisoner::softReset();
	mScore = 0.0f;
}

void GangMember::hardReset()
{
	softReset();
	mVariables[PsiLang::varEnums::CUMULATIVE_SCORE] = 0;
	mCScore = 0.0f;
}

//Both silent
void GangMember::outcomeW(const bool updated)
{
	if (!updated)
	{
		mScore += 2;
	}
	mVariables[PsiLang::varEnums::ALLOUTCOMES_W]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::W;
}

//A silent, B betray
void GangMember::outcomeX(const bool updated)
{
	if (!updated)
	{
		mScore += 5;
	}
	mVariables[PsiLang::varEnums::ALLOUTCOMES_X]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::X;
}

//A betray, B silent
void GangMember::outcomeY(const bool updated)
{
	mVariables[PsiLang::varEnums::ALLOUTCOMES_Y]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::Y;
}

//Both betray
void GangMember::outcomeZ(const bool updated)
{
	if (!updated)
	{
		mScore += 4;
	}
	mVariables[PsiLang::varEnums::ALLOUTCOMES_Z]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::Z;
}

void GangMember::outcomeA(const bool updated)
{
	if (!updated)
	{
		mScore += 2.5;
	}
	mVariables[PsiLang::varEnums::ALLOUTCOMES_A]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::A;
}

void GangMember::outcomeB(const bool updated)
{
	if (!updated)
	{
		mScore += 3;
	}
	mVariables[PsiLang::varEnums::ALLOUTCOMES_B]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::B;
}

void GangMember::outcomeC(const bool updated)
{
	if (!updated)
	{
		mScore += 2;
	}
	mVariables[PsiLang::varEnums::ALLOUTCOMES_C]++;
	mVariables[PsiLang::varEnums::LASTOUTCOME] = PsiLang::varEnums::C;
}

std::ostream& operator<<(std::ostream & os, const GangMember* gm)
{
	os << std::setw(15) << std::left << gm->getStrategyName();
	for (int i = 0; i <= PsiLang::varEnums::ALLOUTCOMES_Z; i++)
	{
		//If LASTOUTCOME print the letter, otherwise print int value of the variable
		if (i == PsiLang::varEnums::LASTOUTCOME)
		{
			os << std::setw(PsiLang::psilVars[i].length() + 2) << PsiLang::psilVars[gm->getVariable(i)];
		}
		//If MYSCORE print var as it's stored as a double and not in the array
		else if (i == PsiLang::varEnums::MYSCORE)
		{
			os << std::setw(PsiLang::psilVars[i].length() + 2) << gm->getScore();
		}
		//If CUMULATIVE_SCORE print var as it's stored as a double and not in the array
		else if (i == PsiLang::varEnums::CUMULATIVE_SCORE)
		{
			os << std::setw(PsiLang::psilVars[i].length() + 2) << gm->getCumulativeScore();
		}
		else
		{
			os << std::setw(PsiLang::psilVars[i].length() + 2) << gm->getVariable(i);
		}
	}
	os << "\n";
	return os;
}
