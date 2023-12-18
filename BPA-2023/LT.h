#pragma once
#define LEXEMA_FIXSIZE	1	
#define LT_MAXSIZE		4096		// ������������ ���������� ����� � ������� ������
#define LT_TI_NULLIDX	0xfffffff	// ��� �������� ������� ���������������



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
#define LEX_LOGICAL		'o'	// ���������� ���������


namespace LT
{
	struct Entry
	{
		unsigned char lexema;
		int numOfString;
		int indexIT;
		int priority;
	};

	struct LexTable						// ��������� ������� ������
	{
		int maxSize;					// ������� ������� ������ < LT_MAXSIZE
		int size;						// ������� ������ ������� ������ < maxSize
		Entry* table;					// ������ ����� ������� ������
	};

	LexTable Create(		// ������� ������� ������
		int size			// ������� ������� ������ < LT_MAXSIZE
	);

	void Add(				// �������� ������ � ������� ������
		LexTable& lexTable,	// ��������� ������� ������
		Entry entry			// ������ ������� ������
	);

	Entry GetEntry(			// �������� ������ ������� ������
		LexTable& lexTable,	// ��������� ������� ������
		int n				// ����� ���������� ������
	);

	void Delete(LexTable& lexTable);	// ������� ������� ������ (���������� ������)

	Entry writeEntry(					// ��������� ������ ������� ������
		Entry& entry,
		unsigned char lexema,
		int indx,
		int line
	);

	void showTable(LexTable lexTable, Log::LOG& log);	// ����� ������� ������
	void show(LexTable lexTable, Parm::PARM parm);
};