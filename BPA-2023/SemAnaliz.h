#pragma once
#include "stdafx.h"

#define PARAMS_MAX 8 //максимальное количество символов в именовании 

#define PREV_ID tables.idTable.table[tables.lexTable.table[i - 1].indexIT]
#define CURR_ID tables.idTable.table[tables.lexTable.table[i].indexIT]
#define NEXT_ID tables.idTable.table[tables.lexTable.table[i + 1].indexIT]

namespace Sem
{
	bool checkSemantic(Lex::LEX& lex, Log::LOG& log);
};