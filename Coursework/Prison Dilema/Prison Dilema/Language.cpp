#include "Language.h"

const std::string Language::psil_keywords[] =
{
	"IF ",
	"GOTO ",
	"BETRAY ",
	"SILENCE ",
	"RANDOM "
};

const std::string Language::psil_operators[] =
{
	"+ ",
	"- ",
	"> ",
	"< ",
	"= ",
	""
};

const std::string Language::psil_vars[] =
{
	"LASTOUTCOME ",
	"ALLOUTCOMES_W ",
	"ALLOUTCOMES_X ",
	"ALLOUTCOMES_Y ",
	"ALLOUTCOMES_Z ",
	"ITERATIONS ",
	"MYSCORE ",
	""
};
