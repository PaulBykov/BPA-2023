#pragma once
#define LEXEMA_FIXSIZE	1	
#define LT_MAXSIZE		4096		// максимальное количество строк в таблице лексем
#define LT_TI_NULLIDX	0xfffffff	// нет элемента таблицы идентификаторов



#define LEX_INCLUDE		'u'	

#define LEX_NUMBER		't'
#define LEX_STRING		't'	
#define LEX_BOOL		't'
#define LEX_SYMBOL		't'

#define LEX_ID			'i'	
#define LEX_LITERAL		'l'	

#define LEX_FUNCTION	'f'	
#define LEX_VAR			'd'	
#define LEX_CONST		'k'	
#define LEX_RETURN		'r'	

#define LEX_WRITE		'p'	
#define LEX_IF			'c'	
#define LEX_ELSE		'e'	
#define LEX_REPEAT		'y'
#define LEX_MAIN		'm'	

#define LEX_POW			'b'	
#define LEX_COMPARE		'a'	

#define LEX_SEMICOLON	';'	
#define LEX_COMMA		','	
#define LEX_LEFTBRACE	'{'
#define LEX_RIGHTBRACE	'}'
#define LEX_LEFTTHESIS	'('
#define LEX_RIGHTTHESIS	')'
#define LEX_EQUAL		'='
#define LEX_PLUS		'+'
#define LEX_MINUS		'-'
#define LEX_LOGICAL		'o'	// логические операторы


namespace LT
{
	struct Entry
	{
		unsigned char lexema;
		int numOfString;
		int indexIT;
		int priority;
	};

	struct LexTable						// экземпл€р таблицы лексем
	{
		int maxSize;					// емкость таблицы лексем < LT_MAXSIZE
		int size;						// текущий размер таблицы лексем < maxSize
		Entry* table;					// массив строк таблицы лексем
	};

	LexTable Create(		// создать таблицу лексем
		int size			// емкость таблицы лексем < LT_MAXSIZE
	);

	void Add(				// добавить строку в таблицу лексем
		LexTable& lexTable,	// экземпл€р таблицы лексем
		Entry entry			// строка таблицы лексем
	);

	Entry GetEntry(			// получить строку таблицы лексем
		LexTable& lexTable,	// экземпл€р таблицы лексем
		int n				// номер получаемой строки
	);

	void Delete(LexTable& lexTable);	// удалить таблицу лексем (освободить пам€ть)

	Entry writeEntry(					// заполнить строку таблицы лексем
		Entry& entry,
		unsigned char lexema,
		int indx,
		int line
	);

	void showTable(LexTable lexTable, Log::LOG& log);	// вывод таблицы лексем
	void show(LexTable lexTable, Parm::PARM parm);
};