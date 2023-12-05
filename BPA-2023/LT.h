#pragma once
#define LEXEMA_FIXSIZE	1			// ������������� ������ �������
#define LT_MAXSIZE		4096		// ������������ ���������� ����� � ������� ������
#define LT_TI_NULLIDX	0xfffffff	// ��� �������� ������� ���������������
#define LEX_INCLUDE		'u'	// ������� ��� uselib
#define LEX_USHORT		't'	// ������� ��� integer
#define LEX_STRING		't'	// ������� ��� string
#define LEX_ID			'i'	// ������� ��� ��������������
#define LEX_LITERAL		'l'	// ������� ��� ��������
#define LEX_FUNCTION	'f'	// ������� ��� function
#define LEX_VAR			'd'	// ������� ��� var
#define LEX_RETURN		'r'	// ������� ��� return
#define LEX_PRINT		'p'	// ������� ��� print
#define LEX_IF			'c'	// ������� ��� if
#define LEX_ELSE		'e'	// ������� ��� else
#define LEX_LOGICAL		'o'	// ������� ��� ���������� ����������
#define LEX_MAIN		'm'	// ������� ��� main
#define LEX_POW			'b'	// ������� ��� pow
#define LEX_COMPARE		'a'	// ������� ��� compare
#define LEX_SEMICOLON	';'	// ������� ��� ;
#define LEX_COMMA		','	// ������� ��� ,
#define LEX_LEFTBRACE	'{'	// ������� ��� {
#define LEX_RIGHTBRACE	'}'	// ������� ��� }
#define LEX_LEFTTHESIS	'('	// ������� ��� (
#define LEX_RIGHTTHESIS	')'	// ������� ��� )
#define LEX_EQUAL		'='
#define LEX_PLUS		'+'
#define LEX_MINUS		'-'
#define LEX_CYCLE		'y'	// ����

namespace LT		// ������� ������
{
	struct Entry	// ������ ������� ������
	{
		unsigned char lexema;	// �������
		int numOfString;				// ����� ������ � �������� ������
		int idxTI;						// ������ � ������� ��������������� ��� LT_TI_NULLIDX
		int priority;					// ���������
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