#include "PsilLang.h"

const std::string PsilLang::psilKeywords[] =
{
	"IF ",
	"GOTO ",
	"BETRAY ",
	"SILENCE ",
	"RANDOM "
};

const std::string PsilLang::psilOperators[] =
{
	"+ ",
	"- ",
	"> ",
	"< ",
	"= ",
};

const std::string PsilLang::psilVars[] =
{
	"LASTOUTCOME ",
	"ALLOUTCOMES_W ",
	"ALLOUTCOMES_X ",
	"ALLOUTCOMES_Y ",
	"ALLOUTCOMES_Z ",
	"ITERATIONS ",
	"MYSCORE ",
	"W ",
	"X ",
	"Y ",
	"Z "
};

const std::map<std::string, int> PsilLang::stringToEnumMap =
{ 
	{ "LASTOUTCOME", PsilLang::varEnums::LASTOUTCOME },
	{ "ALLOUTCOMES_W", PsilLang::varEnums::ALLOUTCOMES_W },
	{ "ALLOUTCOMES_X", PsilLang::varEnums::ALLOUTCOMES_X },
	{ "ALLOUTCOMES_Y", PsilLang::varEnums::ALLOUTCOMES_Y },
	{ "ALLOUTCOMES_Z", PsilLang::varEnums::ALLOUTCOMES_Z },
	{ "ITERATIONS", PsilLang::varEnums::ITERATIONS },
	{ "MYSCORE", PsilLang::varEnums::MYSCORE },
	{ "W", PsilLang::varEnums::W },
	{ "X", PsilLang::varEnums::X},
	{ "Y", PsilLang::varEnums::Y },
	{ "Z", PsilLang::varEnums::Z }
};
