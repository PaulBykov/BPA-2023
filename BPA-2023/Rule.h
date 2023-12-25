#pragma once
#include "stdafx.h"

#define GRB_ERROR_SERIES 300

#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)


#define FUNC_CALL TS('i'), TS('('), NS('W'), TS(')')
#define POW_CALL TS('a'), TS('('), NS('W'), TS(')')
#define COMPARE_CALL TS('b'), TS('('), NS('W'), TS(')')


namespace GRB
{
	Greibach greibach(
		NS('S'), // стартовый символ
		TS('$'), //дно стека      
		6,
		Rule(
			NS('S'),
			GRB_ERROR_SERIES + 0,    // неверная структура программы
			7,
			Rule::Chain(2, TS('u'), TS('l')),
			Rule::Chain(3, TS('u'), TS('l'), NS('S')),
			Rule::Chain(7, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(11, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S'))
		),
		Rule(
			NS('N'),
			GRB_ERROR_SERIES + 1,    // ошибка в конструкции
			18,
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),

			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),

			Rule::Chain(7, TS('k'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),

			Rule::Chain(6, TS('p'), TS('('), TS('i'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(6, TS('p'), TS('('), TS('l'), TS(')'), TS(';'), NS('N')),

			Rule::Chain(12, TS('c'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'), TS('e'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(8, TS('c'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),


			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),

			Rule::Chain(5, TS('p'), TS('('), TS('i'), TS(')'), TS(';')),
			Rule::Chain(5, TS('p'), TS('('), TS('l'), TS(')'), TS(';')),

			Rule::Chain(6, TS('k'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),

			Rule::Chain(11, TS('c'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'), TS('e'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(7, TS('c'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}')),

			Rule::Chain(8, TS('y'), TS('('), TS('i'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(8, TS('y'), TS('('), TS('l'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(7, TS('y'), TS('('), TS('i'), TS(')'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(7, TS('y'), TS('('), TS('l'), TS(')'), TS('{'), NS('N'), TS('}'))

		),
		Rule(
			NS('E'),
			GRB_ERROR_SERIES + 2,    // ошибка в выражении
			15,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),

			Rule::Chain(3, TS('i'), TS('+'), NS('E')),
			Rule::Chain(3, TS('l'), TS('+'), NS('E')),
			Rule::Chain(3, TS('i'), TS('-'), NS('E')),
			Rule::Chain(3, TS('l'), TS('-'), NS('E')),

			Rule::Chain(4, FUNC_CALL),
			Rule::Chain(4, POW_CALL),
			Rule::Chain(4, COMPARE_CALL),

			Rule::Chain(6, FUNC_CALL, TS('+'), NS('E')),
			Rule::Chain(6, POW_CALL, TS('+'), NS('E')),
			Rule::Chain(6, COMPARE_CALL, TS('+'), NS('E')),
			Rule::Chain(6, FUNC_CALL, TS('-'), NS('E')),
			Rule::Chain(6, POW_CALL, TS('-'), NS('E')),
			Rule::Chain(6, COMPARE_CALL, TS('-'), NS('E'))
		),
		Rule(
			NS('F'),
			GRB_ERROR_SERIES + 3,    // ошибка в параметрах функции
			2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(
			NS('W'),
			GRB_ERROR_SERIES + 4,    // ошибка в параметрах вызываемой функции 
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(
			NS('C'),
			GRB_ERROR_SERIES + 5,    // условие if
			4,
			Rule::Chain(3, TS('i'), TS('o'), TS('i')),
			Rule::Chain(3, TS('i'), TS('o'), TS('l')),
			Rule::Chain(3, TS('l'), TS('o'), TS('i')),
			Rule::Chain(3, TS('l'), TS('o'), TS('l'))
		)
	);
}