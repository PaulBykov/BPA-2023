#include "stdafx.h"

namespace In
{

	IN getin(wchar_t infile[])
	{
		int currentLine = 0, currentCol = 0;
		IN Info{ 0, 0, 0, nullptr, IN_CODE_TABLE };					//uniform ������������� (������������ == ������ �������������)
		std::ifstream in(infile);

		if (!in.is_open()) {
			throw ERROR_THROW(110);
		}

		std::string fulltext;
		std::string temp;

		while (!in.eof())
		{
			Info.lines++;
			std::getline(in, temp);
			temp += "\n";
			fulltext += temp;
		}

		Info.text = new unsigned char[fulltext.size() + 1];
		unsigned char* Ptemp = Info.text;
		for (int i = 0; i < fulltext.size(); ++i)
		{
			if ((Info.code[(unsigned char)fulltext[i]] == IN::F)) {
				throw ERROR_THROW_IN(111, currentLine + 1, currentCol)
			}
			else if (Info.code[(unsigned char)fulltext[i]] == IN::I) {
				++Info.ignor;
			}
			else if ((Info.code[(unsigned char)fulltext[i]] == IN::T) || (Info.code[(unsigned char)fulltext[i]] == IN::S))// ���� ����������� ������ 
			{
				*Ptemp = fulltext[i];
				++Ptemp;
			}
			else													//���� �� ������ ������ ,  ������ ������� ����� ���� �� 1
			{
				*Ptemp = Info.code[(unsigned char)fulltext[i]];
				++Ptemp;
			}
			if (fulltext[i] == '\n')								//���� ����� ������, ������ ������� ������ �� 1 
			{
				++currentLine;
				currentCol = 0;
			}
			else
				++currentCol;
		}
		*Ptemp = IN_CODE_ENDL;
		Info.size = strlen((char*)Info.text);			//���������� ������� = ���������� ���� ���� - \n
		unsigned char* str = new unsigned char[Info.size];
		in.close();
		return Info;
	}
}