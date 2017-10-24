#include "PsilLang.h"

const std::string PsilLang::psilKeywords[] =
{
	"IF",
	"GOTO",
	"BETRAY",
	"SILENCE",
	"RANDOM"
};

const std::string PsilLang::psilOperators[] =
{
	"+",
	"-",
	">",
	"<",
	"=",
};

const std::string PsilLang::psilVars[] =
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

const std::map<std::string, int> PsilLang::stringToEnumMap =
{
	{ "LASTOUTCOME", PsilLang::varEnums::LASTOUTCOME },
	{ "ITERATIONS", PsilLang::varEnums::ITERATIONS },
	{ "MYSCORE", PsilLang::varEnums::MYSCORE },
	{ "ALLOUTCOMES_W", PsilLang::varEnums::ALLOUTCOMES_W },
	{ "ALLOUTCOMES_X", PsilLang::varEnums::ALLOUTCOMES_X },
	{ "ALLOUTCOMES_Y", PsilLang::varEnums::ALLOUTCOMES_Y },
	{ "ALLOUTCOMES_Z", PsilLang::varEnums::ALLOUTCOMES_Z },
	{ "INTEGER_PLACEHOLDER_1", PsilLang::varEnums::INTEGER_PLACEHOLDER_1 },
	{ "ALLOUTCOMES_A", PsilLang::varEnums::ALLOUTCOMES_A },
	{ "ALLOUTCOMES_B", PsilLang::varEnums::ALLOUTCOMES_B },
	{ "ALLOUTCOMES_C", PsilLang::varEnums::ALLOUTCOMES_C },
	{ "INTEGER_PLACEHOLDER_2", PsilLang::varEnums::INTEGER_PLACEHOLDER_2 },
	{ "W", PsilLang::varEnums::W },
	{ "X", PsilLang::varEnums::X },
	{ "Y", PsilLang::varEnums::Y },
	{ "Z", PsilLang::varEnums::Z },
	{ "A", PsilLang::varEnums::A },
	{ "B", PsilLang::varEnums::B },
	{ "C", PsilLang::varEnums::C },
	{ "-", PsilLang::varEnums::UNKOWN_DECISION },
	{ "CUMULATIVE_SCORE", PsilLang::varEnums::CUMULATIVE_SCORE }
};
