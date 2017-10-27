#include "PsiLang.h"

const std::string PsiLang::psilKeywords[] =
{
	"IF",
	"GOTO",
	"BETRAY",
	"SILENCE",
	"RANDOM"
};

const std::string PsiLang::psilOperators[] =
{
	"+",
	"-",
	">",
	"<",
	"=",
};

const std::string PsiLang::psilVars[] =
{
	"LASTOUTCOME",
	"ITERATIONS",
	"MYSCORE",
	"ALLOUTCOMES_W",
	"ALLOUTCOMES_X",
	"ALLOUTCOMES_Y",
	"ALLOUTCOMES_Z",
	"INTEGER_PLACEHOLDER_1",	//should never be used
	"ALLOUTCOMES_A",
	"ALLOUTCOMES_B",
	"ALLOUTCOMES_C",
	"INTEGER_PLACEHOLDER_2",	//should never be used
	"W",
	"X",
	"Y",
	"Z",
	"A",
	"B",
	"C",
	"-",			//Unknown decision - decisions will be initialised with this
	"CUMULATIVE_SCORE"
};

const std::map<std::string, int> PsiLang::stringToEnumMap =
{
	{ "LASTOUTCOME", PsiLang::varEnums::LASTOUTCOME },
	{ "ITERATIONS", PsiLang::varEnums::ITERATIONS },
	{ "MYSCORE", PsiLang::varEnums::MYSCORE },
	{ "ALLOUTCOMES_W", PsiLang::varEnums::ALLOUTCOMES_W },
	{ "ALLOUTCOMES_X", PsiLang::varEnums::ALLOUTCOMES_X },
	{ "ALLOUTCOMES_Y", PsiLang::varEnums::ALLOUTCOMES_Y },
	{ "ALLOUTCOMES_Z", PsiLang::varEnums::ALLOUTCOMES_Z },
	{ "INTEGER_PLACEHOLDER_1", PsiLang::varEnums::INTEGER_PLACEHOLDER_1 },
	{ "ALLOUTCOMES_A", PsiLang::varEnums::ALLOUTCOMES_A },
	{ "ALLOUTCOMES_B", PsiLang::varEnums::ALLOUTCOMES_B },
	{ "ALLOUTCOMES_C", PsiLang::varEnums::ALLOUTCOMES_C },
	{ "INTEGER_PLACEHOLDER_2", PsiLang::varEnums::INTEGER_PLACEHOLDER_2 },
	{ "W", PsiLang::varEnums::W },
	{ "X", PsiLang::varEnums::X },
	{ "Y", PsiLang::varEnums::Y },
	{ "Z", PsiLang::varEnums::Z },
	{ "A", PsiLang::varEnums::A },
	{ "B", PsiLang::varEnums::B },
	{ "C", PsiLang::varEnums::C },
	{ "-", PsiLang::varEnums::UNKOWN_DECISION },
	{ "CUMULATIVE_SCORE", PsiLang::varEnums::CUMULATIVE_SCORE }
};
