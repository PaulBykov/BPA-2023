#pragma once
#define ID_MAXSIZE		8			// ������������ ���������� �������� � ��������������
#define REGION_MAXSIZE	16			// ������������ ���������� �������� � �������������� c ���������
#define TI_MAXSIZE		4096		// ������������ ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT	0x0000		// �������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT	""		// �������� �� ��������� ��� ���� string
#define TI_NULLIDX		0xffff		// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255			// ����� ������

#include <variant>

namespace IT
{
	enum IDDATATYPE { NUM = 1, STR = 2, CHR = 3, BOOL = 4 };			// ���� ������ ���������������: integer, string
	enum IDTYPE { VAR = 1, FUNC = 2, PARM = 3, LIT = 4, OP = 5, LIB = 6, CONST = 7 };	// ���� ���������������: ����������, �������, ��������, �������, ��������, ������������ �������, ���������

	using allowedTypes = variant<short, string>;

	struct Entry
	{
		int			indexLT;
		unsigned char	idRegion[REGION_MAXSIZE];		// �������� ������� ��������� + id
		unsigned char	id[ID_MAXSIZE];
		IDDATATYPE	idDataType;
		IDTYPE		idType;

		allowedTypes value;
		bool defined = false;
	};


	struct IdTable				// ��������� ������� ���������������
	{
		int maxSize;			// ������� ������� ��������������� < TI_MAXSIZE
		int size;				// ������� ������ ������� ��������������� < maxSize
		Entry* table;			// ������ ����� ������� ���������������
	};

	IdTable Create(				// ������� ������� ���������������
		int size				// ������� ������� ��������������� < TI_MAXSIZE
	);

	void Add(				// �������� ������ � ������� ���������������
		IdTable& idTable,	// ��������� ������� ���������������
		Entry entry			// ������ ������� ���������������
	);

	Entry GetEntry(			// �������� ������ ������� ���������������
		IdTable& idTable,	// ��������� ������� ���������������
		int n				// ����� ���������� ������
	);

	int IsIDRegion(				// �������: ����� ������ (���� ����), TI_NULLIDX (���� ���)
		IdTable& idTable,	// ��������� ������� ���������������
		unsigned char id[ID_MAXSIZE]	// �������������
	);

	void Delete(IdTable& idTable);	// ������� ������� ��������������� (���������� ������)
	void showTable(IdTable& idTable, Log::LOG& log);
	void show(IdTable& idTable, Parm::PARM parm);
};