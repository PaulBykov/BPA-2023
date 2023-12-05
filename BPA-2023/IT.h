#pragma once
#define ID_MAXSIZE		8			// ������������ ���������� �������� � ��������������
#define REGION_MAXSIZE	16			// ������������ ���������� �������� � �������������� c ���������
#define TI_MAXSIZE		4096		// ������������ ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT	0x0000		// �������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT	0x00		// �������� �� ��������� ��� ���� string
#define TI_NULLIDX		0xffff		// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255			// ����� ������

namespace IT			// ������� ���������������
{
	enum IDDATATYPE { USHORT = 1, STR = 2, CHR = 3, BOOL = 4};			// ���� ������ ���������������: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, OP = 5, LIB = 6 };	// ���� ���������������: ����������, �������, ��������, 
																	// �������, ��������, ������������ �������

	struct Entry	// ������ ������� ���������������
	{
		int			idxfirstLE;						// ������ ������ ������ � ������� ������
		unsigned char	idRegion[REGION_MAXSIZE];	// �������� ��� ������� ���������
		unsigned char	id[ID_MAXSIZE];				// �������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE	idDataType;						// ��� ������
		IDTYPE		idType;							// ��� ��������������
		union
		{
			signed short number;								// �������� integer
			bool isChar = false;
			struct
			{
				unsigned char len;						// ���������� �������� � string
				unsigned char str[TI_STR_MAXSIZE - 1];	// ������� string
			} vstr;				// �������� string
		} value;		// �������� ��������������
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