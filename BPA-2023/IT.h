#pragma once
#define ID_MAXSIZE		8			// максимальное количество символов в идентификаторе
#define REGION_MAXSIZE	16			// максимальное количество символов в идентификаторе c префиксом
#define TI_MAXSIZE		4096		// максимальное количество строк в таблице идентификаторов
#define TI_INT_DEFAULT	0x0000		// значение по умолчанию дл€ типа integer
#define TI_STR_DEFAULT	""		// значение по умолчанию дл€ типа string
#define TI_NULLIDX		0xffff		// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	255			// длина строки

#include <variant>

namespace IT
{
	enum IDDATATYPE { NUM = 1, STR = 2, CHR = 3, BOOL = 4 };			// типы данных идентификаторов: integer, string
	enum IDTYPE { VAR = 1, FUNC = 2, PARM = 3, LIT = 4, OP = 5, LIB = 6, CONST = 7 };	// типы идентификаторов: переменна€, функци€, параметр, литерал, оператор, библиотечна€ функци€, константа

	using allowedTypes = variant<short, string>;

	struct Entry
	{
		int			indexLT;
		unsigned char	idRegion[REGION_MAXSIZE];		// префиксы области видимости + id
		unsigned char	id[ID_MAXSIZE];
		IDDATATYPE	idDataType;
		IDTYPE		idType;

		allowedTypes value;
		bool defined = false;
	};


	struct IdTable				// экземпл€р таблицы идентификаторов
	{
		int maxSize;			// емкость таблицы идентификаторов < TI_MAXSIZE
		int size;				// текущий размер таблицы идентификаторов < maxSize
		Entry* table;			// массив строк таблицы идентификаторов
	};

	IdTable Create(				// создать таблицу идентификаторов
		int size				// емкость таблицы идентификаторов < TI_MAXSIZE
	);

	void Add(				// добавить строку в таблицу идентификаторов
		IdTable& idTable,	// экземпл€р таблицы идентификаторов
		Entry entry			// строка таблицы идентификаторов
	);

	Entry GetEntry(			// получить строку таблицы идентификаторов
		IdTable& idTable,	// экземпл€р таблицы идентификаторов
		int n				// номер получаемой строки
	);

	int IsIDRegion(				// возврат: номер строки (если есть), TI_NULLIDX (если нет)
		IdTable& idTable,	// экземпл€р таблицы идентификаторов
		unsigned char id[ID_MAXSIZE]	// идентификатор
	);

	void Delete(IdTable& idTable);	// удалить таблицу идентификаторов (освободить пам€ть)
	void showTable(IdTable& idTable, Log::LOG& log);
	void show(IdTable& idTable, Parm::PARM parm);
};