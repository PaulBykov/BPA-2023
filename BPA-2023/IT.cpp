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
		Table.table = new Entry[size];
		return Table;
	}

	void Add(IdTable& idTable, Entry entry)
	{
		if (idTable.size > idTable.maxSize) throw ERROR_THROW(205);
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
			case USHORT:
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
			case V: *log.stream << "���������� > "; break;
			case F: *log.stream << "������� > "; break;
			case P: *log.stream << "�������� > "; break;
			case L: *log.stream << "������� > "; break;
			case OP:
				*log.stream << "�������� > ";
				numberOP++;
				break;
			default: *log.stream << "unknown > "; break;
			}
			*log.stream << idTable.table[i].idxfirstLE << " > ";
			if (idTable.table[i].idDataType == USHORT && (idTable.table[i].idType == V || idTable.table[i].idType == L))
				*log.stream << std::left << idTable.table[i].value.number;
			else if (idTable.table[i].idDataType == STR && (idTable.table[i].idType == V || idTable.table[i].idType == L))
				*log.stream << "[" << (int)idTable.table[i].value.vstr.len << "]\"" << idTable.table[i].value.vstr.str << "\"";
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
			switch (idTable.table[i].idDataType)
			{
			case USHORT:
				if (!(idTable.table[i].idType == OP))
					cout<< "number" << " > "; break;
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
			switch (idTable.table[i].idType)
			{
			case V: cout << "���������� > "; break;
			case F: cout << "������� > "; break;
			case P: cout << "�������� > "; break;
			case L: cout << "������� > "; break;
			case OP:
				cout<< "�������� > ";
				numberOP++;
				break;
			default: cout << "unknown > "; break;
			}
			cout << idTable.table[i].idxfirstLE << " > ";
			if (idTable.table[i].idDataType == USHORT && (idTable.table[i].idType == V || idTable.table[i].idType == L))
				cout<< std::left << idTable.table[i].value.number;
			else if (idTable.table[i].idDataType == STR && (idTable.table[i].idType == V || idTable.table[i].idType == L))
				cout << "[" << (int)idTable.table[i].value.vstr.len << "]\"" << idTable.table[i].value.vstr.str << "\"";
			else
				cout << "��� ��������";
			cout << std::endl;
		}
		cout << std::setfill('*') << std::setw(40) << '*' << std::setfill(' ') << std::setw(1) << std::endl;
		cout << "���������� ���������������: " << i - numberOP << std::endl;
	}
}