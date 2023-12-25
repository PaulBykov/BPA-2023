#include "stdafx.h"

unsigned char** divideText(In::IN in)
{
	int size = in.size;
	unsigned char* text = in.text;
	unsigned char** word = new unsigned char* [MAX_WORDS]; //выделение памяти для разделения лексем

	for (int i = 0; i < MAX_WORDS; i++) {
		word[i] = new unsigned char[WORD_SIZE] {NULL};
	}

	bool findSP, findLit = false;	//флаги сепараторов и литералов

	int j = 0;

	for (int i = 0, k = 0; i < size - 1; i++, k++)
	{
		if (text[i] == '[') {
			for (i++; text[i] != ']';)
				i++;
			i++;
		}

		findSP = false;

		if (text[i] == '?') {
			do {
				i++;
			} while (text[i] != '?' && i < size - 1);
			i++;
		}

		if (text[i] == '\"') // случаи комментария или строкового литерала
			findLit = !findLit;

		if (((in.code[(unsigned char)text[i]] == In::IN::S) ||
			(text[i] == DIV)) && !findLit) //проверка на сепаратор
		{
			findSP = true;
			if (word[j][0] != NULL)
			{
				word[j++][k] = IN_CODE_ENDL; // конец слова
				k = 0;
			}
			if (text[i] == ' ') //если пробел - пропускаем
			{
				k = -1;
				continue;
			}

			word[j][k++] = text[i]; //запись сепаратора
			if (text[i + 1] == LEX_EQUAL)
			{
				word[j][k++] = text[++i];	// запись логических операторов
			}

			word[j++][k] = IN_CODE_ENDL;
			k = -1;
		}

		if (!findSP)		//если не сепаратор -> оставим как есть
			word[j][k] = text[i];
	}
	word[j] = NULL;

	return word;
}
