#include "stdafx.h"

namespace IT
{
	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE)
			throw ERROR_THROW(204);

		IdTable Table;
		Table.maxSize = size;
		Table.size = 0;

		Table.table = (new Entry[size]);

		return Table;
	}

	void Add(IdTable& idTable, Entry entry)
	{
		if (idTable.size > idTable.maxSize)
			throw ERROR_THROW(205);

		idTable.table[idTable.size++] = entry;
	}

	Entry GetEntry(IdTable& idTable, int n)
	{
		return idTable.table[n];
	}

	int IsIDRegion(IdTable& idTable, unsigned char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idTable.size; i++)
		{
			if (_mbscmp(idTable.table[i].idRegion, id) == 0)
				return i;
		}

		return TI_NULLIDX;
	}

	void Delete(IdTable& idTable)
	{
		idTable.maxSize = NULL;
		idTable.size = NULL;
		delete[] idTable.table;
	}

	void showTable(IdTable& idTable, Log::LOG& log)
	{
		int i, numberOP = 0;
		*log.stream << "\n\n� > ������������� > ������� ��������� > ��� ������ > ��� �������������� > ������ � �� > ��������\n\n";
		for (i = 0; i < idTable.size; i++)
		{
			*log.stream << i << " > ";
			*log.stream << idTable.table[i].id << " > ";
			*log.stream << idTable.table[i].idRegion << " > ";
			switch (idTable.table[i].idDataType)
			{
			case NUM:
				if (!(idTable.table[i].idType == OP))
					*log.stream << "number" << " > "; break;
			case STR:
				if (!(idTable.table[i].idType == OP))
					*log.stream << "string" << " > "; break;
			case CHR:
				if (!(idTable.table[i].idType == OP))
					*log.stream << "char" << " > "; break;
			case BOOL:
				if (!(idTable.table[i].idType == OP))
					*log.stream << "bool" << " > "; break;
			default: *log.stream << "unknown" << " > "; break;
			}

			switch (idTable.table[i].idType)
			{
			case VAR: *log.stream << "���������� > "; break;
			case FUNC: *log.stream << "������� > "; break;
			case PARM: *log.stream << "�������� > "; break;
			case LIT: *log.stream << "������� > "; break;
			case OP:
				*log.stream << "�������� > ";
				numberOP++;
				break;
			default: *log.stream << "unknown > "; break;
			}

			*log.stream << idTable.table[i].indexLT << " > ";

			if (idTable.table[i].idDataType == NUM
				&& (idTable.table[i].idType == VAR
					|| idTable.table[i].idType == LIT))
			{
				*log.stream << std::left << get<short>(idTable.table[i].value);
			}
			else if (idTable.table[i].idDataType == STR
				&& (idTable.table[i].idType == VAR
					|| idTable.table[i].idType == LIT))
			{
				*log.stream << "[" << (int)get<string>(idTable.table[i].value).length()
					<< "]\"" << get<string>(idTable.table[i].value) << "\"";
			}
			else
				*log.stream << "��� ��������";
			*log.stream << std::endl;
		}
		*log.stream << std::setfill('*') << std::setw(40) << '*' << std::setfill(' ') << std::setw(1) << std::endl;
		*log.stream << "���������� ���������������: " << i - numberOP << std::endl;
	}
	void show(IdTable& idTable, Parm::PARM parm)
	{
		int i, numberOP = 0;
		cout << "\n\n� > ������������� > ������� ��������� > ��� ������ > ��� �������������� > ������ � �� > ��������\n\n";
		for (i = 0; i < idTable.size; i++)
		{
			cout << i << " > ";
			cout << idTable.table[i].id << " > ";
			cout << idTable.table[i].idRegion << " > ";


			switch (idTable.table[i].idDataType) {
			case NUM:
				if (!(idTable.table[i].idType == OP))
					cout << "number" << " > "; break;
			case STR:
				if (!(idTable.table[i].idType == OP))
					cout << "string" << " > "; break;
			case CHR:
				if (!(idTable.table[i].idType == OP))
					cout << "char" << " > "; break;
			case BOOL:
				if (!(idTable.table[i].idType == OP))
					cout << "bool" << " > "; break;
			default: cout << "unknown" << " > "; break;
			}


			switch (idTable.table[i].idType) {
			case VAR: cout << "���������� > "; break;
			case FUNC: cout << "������� > "; break;
			case PARM: cout << "�������� > "; break;
			case LIT: cout << "������� > "; break;
			case OP:
				cout << "�������� > ";
				numberOP++;

				break;
			case CONST:
				cout << "��������� > "; break;
			default: cout << "unknown > "; break;
			}


			cout << idTable.table[i].indexLT << " > ";
			if (idTable.table[i].idDataType == NUM
				&& (idTable.table[i].idType == VAR
					|| idTable.table[i].idType == LIT))
			{
				cout << std::left << get<short>(idTable.table[i].value);
			}

			else if (idTable.table[i].idDataType == STR && (idTable.table[i].idType == VAR || idTable.table[i].idType == LIT)) {
				cout << "[" << get<string>(idTable.table[i].value).length() << "]\"" << get<string>(idTable.table[i].value) << "\"";
			}
			else {
				cout << "��� ��������";
			}

			cout << std::endl;
		}
		cout << std::setfill('*') << std::setw(40) << '*' << std::setfill(' ') << std::setw(1) << std::endl;
		cout << "���������� ���������������: " << i - numberOP << std::endl;
	}
}