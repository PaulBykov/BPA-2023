#include "stdafx.h"

#pragma warning(disable:4996)

#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define SLASH '/'
#define EQUAL '='

#define TO_STR (string)(char*)

#define ADD_TO_LEX(lex) \
	LT::Entry entryLT; \
	writeEntry(entryLT, lex, LT_TI_NULLIDX, line); \
	LT::Add(lexTable, entryLT); \
	

using namespace std;

namespace Lex
{
	LEX lexAnaliz(Log::LOG log, In::IN in)
	{
		LEX lex;
		LT::LexTable lexTable = LT::Create(LT_MAXSIZE); //создание таблицы лексем макс размера
		IT::IdTable idTable = IT::Create(TI_MAXSIZE);//создание таблицы индефикаторов макс размера

		unsigned char** word = new unsigned char* [MAX_WORDS]; //выделение памяти для разделения лексем
		for (int i = 0; i < MAX_WORDS; i++)
			word[i] = new unsigned char[WORD_SIZE] {NULL};

		word = divideText(in); //разделение на лексемы 


		int indexLex = 0;		// индекс лексемы
		int indexID = 0;		// индекс идент.
		int countLit = 1;		// счетчик литералов
		int line = 1;			// номер строки
		int mainFuncCount = 0;		// кол-во main

		unsigned char emptystr[] = "";
		unsigned char* regionPrefix = new unsigned char[10] { "" };	// текущий префикс
		unsigned char* bufRegionPrefix = new unsigned char[10] { "" };	// буфер для префикса
		unsigned char* oldRegionPrefix = new unsigned char[10] { "" };	// предыдущий префикс
		unsigned char* L = new unsigned char[2] { "L" };		// начальный символ для имён литералов + \0
		unsigned char* bufL = new unsigned char[TI_STR_MAXSIZE];
		unsigned char* nameLiteral = new unsigned char[TI_STR_MAXSIZE] { "" };

		char* charCountLit = new char[10] { "" };		// для строковой записи счетчика
		unsigned char* startWord = new unsigned char[WORD_SIZE] {NULL}; //для области видимости

		bool findFunc = false;
		bool findParm = false;
		bool findDeclaration = false;

		IT::Entry entryIT; 

		for (int i = 0; word[i] != NULL; i++, indexLex++) //проход по всем лексемам
		{
			bool findSameID = false;

			FST::FST fstComment(word[i], FST_COMMENT);
			if (FST::execute(fstComment)) {
				line++;
				continue;
			}

			FST::FST fstLib(word[i], FST_INCLUDE);
			if (FST::execute(fstLib))
			{
				ADD_TO_LEX(LEX_INCLUDE)
				continue;
			}

			FST::FST fstIf(word[i], FST_IF);
			if (FST::execute(fstIf))
			{
				ADD_TO_LEX(LEX_IF)
				continue;
			}

			FST::FST fstElse(word[i], FST_ELSE);
			if (FST::execute(fstElse))
			{
				ADD_TO_LEX(LEX_ELSE)
				continue;
			}
			FST::FST fstCycle(word[i], FST_REPEAT);
			if (FST::execute(fstCycle))
			{
				ADD_TO_LEX(LEX_CYCLE)
				continue;
			}

			FST::FST fstLogical(word[i], FST_LOGICAL);
			if (FST::execute(fstLogical))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LOGICAL, indexID++, line); //создание структуры
				LT::Add(lexTable, entryLT); //добавление структуры в таблицу
				_mbscpy(entryIT.id, word[i]);

				entryIT.idxfirstLE = indexLex;
				entryIT.idType = IT::OP;
				IT::Add(idTable, entryIT);
				continue;
			}

			FST::FST fstDeclare(word[i], FST_DECLARE);
			if (FST::execute(fstDeclare))
			{
				ADD_TO_LEX(LEX_VAR)
				continue;
			}

			FST::FST fstTypeInteger(word[i], FST_NUMBER);
			if (FST::execute(fstTypeInteger))
			{
				ADD_TO_LEX(LEX_USHORT)
				entryIT.idDataType = IT::USHORT; //запись типа идентификатора в структуру

				findDeclaration = true;
				continue;
			}

			FST::FST fstTypeString(word[i], FST_STRING);
			if (FST::execute(fstTypeString))
			{
				ADD_TO_LEX(LEX_STRING)

				entryIT.idDataType = IT::STR;			//запись типа идентификатора в структуру
				_mbscpy(entryIT.value.vstr.str, emptystr); //очистка строки для записи идентификатора

				findDeclaration = true;
				continue;
			}

			FST::FST fstTypeSymbol(word[i], FST_SYMBOL);
			if (FST::execute(fstTypeSymbol))
			{
				//std::cout << "i = " << i << " word[i] = " << word[i] << " word[i+1] = " << word[i + 1] << "\t" << word[i + 2] << "\n";
				
				ADD_TO_LEX(LEX_STRING)
				entryIT.idDataType = IT::STR;				//запись типа идентификатора в структуру
				_mbscpy(entryIT.value.vstr.str, emptystr); //очистка строки для записи идентификатора

				findDeclaration = true;
				continue;
			}

			FST::FST fstTypeBool(word[i], FST_BOOL);
			if (FST::execute(fstTypeBool))
			{
				ADD_TO_LEX(LEX_USHORT)
				entryIT.idDataType = IT::BOOL; //запись типа идентификатора в структуру

				findDeclaration = true;
				continue;
			}

			FST::FST fstFunction(word[i], FST_FUNCTION);
			if (FST::execute(fstFunction))
			{
				ADD_TO_LEX(LEX_FUNCTION)

				entryIT.idType = IT::F;
				findFunc = true; //установка флага функции
				continue;
			}

			FST::FST fstReturn(word[i], FST_RETURN);
			if (FST::execute(fstReturn))
			{
				ADD_TO_LEX(LEX_RETURN)
				continue;
			}

			FST::FST fstPrint(word[i], FST_WRITE);
			if (FST::execute(fstPrint))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_PRINT, indexID++, line);
				LT::Add(lexTable, entryLT);

				entryIT.idType = IT::LIB;
				entryIT.idxfirstLE = indexLex;

				_mbscpy(entryIT.id, word[i]);
				_mbscpy(entryIT.idRegion, word[i]);
				IT::Add(idTable, entryIT);
				continue;
			}

			FST::FST fstMain(word[i], FST_MAIN);
			if (FST::execute(fstMain))
			{
				ADD_TO_LEX(LEX_MAIN)
				mainFuncCount++;
				_mbscpy(oldRegionPrefix, regionPrefix);
				_mbscpy(regionPrefix, word[i]);
				continue;
			}

			FST::FST fstLiteralFalse(word[i], FST_BOOLLIT1);
			FST::FST fstLiteralTrue(word[i], FST_BOOLLIT2);

			if (FST::execute(fstLiteralFalse) || FST::execute(fstLiteralTrue)) {
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lexTable, entryLT);

				entryIT.idType = IT::L;
				entryIT.idDataType = IT::BOOL;

				entryIT.value.number = 1;
				if (word[i][0] == 'f') {		// если false
					entryIT.value.number = 0;
				}
				
				entryIT.idxfirstLE = indexLex;	//номер в табл лексем
				_itoa_s(countLit++, charCountLit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charCountLit) 

				// формирование имени литерала
				_mbscpy(bufL, L);	// помещаем в буфер "L"
				word[i] = _mbscat(bufL, (unsigned char*)charCountLit);	// формируем имя для литерала
				_mbscpy(entryIT.id, word[i]);
				_mbscpy(entryIT.idRegion, word[i]);
				IT::Add(idTable, entryIT);
				continue;
			}


			FST::FST fstIdentif(word[i], FST_ID);
			if (FST::execute(fstIdentif))
			{
				FST::FST fstLibPow(word[i], FST_LIB_POW); 
				FST::FST fstLibCompare(word[i], FST_LIB_COMPARE); 

				if (_mbslen(word[i]) > ID_MAXSIZE)
					throw ERROR_THROW_IN(202, line, 0);
				_mbscpy(startWord, word[i]);


				if (findFunc)	// если функция
				{
					int idx = IT::IsIDRegion(idTable, word[i]);	// ищем без префикса
					if (idx != TI_NULLIDX)						// если такой идентификатор уже есть
					{
						if (lexTable.table[indexLex - 1].lexema == LEX_FUNCTION)
							throw ERROR_THROW_IN(200, line, 0);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lexTable, entryLT);
						findFunc = false;
						continue;
					}
				}
				else
				{
					int idx = IT::IsIDRegion(idTable, word[i]);
					if (idx != TI_NULLIDX)
					{
						if (lexTable.table[indexLex - 2].lexema == LEX_VAR)
							throw ERROR_THROW_IN(200, line, 0);

						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lexTable, entryLT);
						continue;
					}
					_mbscpy(bufRegionPrefix, regionPrefix);
					word[i] = _mbscat(bufRegionPrefix, word[i]);
					idx = IT::IsIDRegion(idTable, word[i]);

					if (idx != TI_NULLIDX)		// если такой идентификатор уже есть
					{
						if (lexTable.table[indexLex - 2].lexema == LEX_VAR)
							throw ERROR_THROW_IN(200, line, 0);
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lexTable, entryLT);
						continue;
					}
				}
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_ID, indexID++, line);

				if (findParm)				// если параметр
				{
					entryIT.idType = IT::P;
				}
				else if (!findFunc)
				{
					// если переменная
					if (findDeclaration)
					{
						entryIT.idType = IT::V;
						
						if (entryIT.idDataType == IT::USHORT)
							entryIT.value.number = TI_INT_DEFAULT;
						
						if (entryIT.idDataType == IT::STR) {
							entryIT.value.vstr.len = 0;
							memset(entryIT.value.vstr.str, TI_STR_DEFAULT, sizeof(char));
						}

						if (entryIT.idDataType == IT::BOOL) {
							entryIT.value.number = 0;
						}

						findDeclaration = false;
					}
					else
					{
						FST::FST fstLibCompare(startWord, FST_LIB_COMPARE);
						
						if (FST::execute(fstLibCompare))
						{
							entryLT.lexema = LEX_COMPARE;
							entryIT.idType = IT::LIB;
						}
						else
						{
							throw ERROR_THROW_IN(203, line, i);
						}
					}
				}
				else {		// если функция
					_mbscpy(oldRegionPrefix, regionPrefix);
					_mbscpy(regionPrefix, word[i]);
				}

				LT::Add(lexTable, entryLT);
				entryIT.idxfirstLE = indexLex;
				_mbscpy(entryIT.id, startWord);
				_mbscpy(entryIT.idRegion, word[i]);
				IT::Add(idTable, entryIT);
				findFunc = false;
				continue;
			}

			FST::FST fstLiteralInt(word[i], FST_INTLIT); //если литерал 

			if (FST::execute(fstLiteralInt))
			{
				short value;
				char* buf;
				if (atoi((char*)word[i]) > MAX_NUMBER)
					throw ERROR_THROW_IN(208, line, i);


				value = atoi((char*)word[i]);

				for (int k = 0; k < idTable.size; k++) // поиск такого же
				{
					if (idTable.table[k].value.number == value && idTable.table[k].idType == IT::L)
					{
						LT::Entry entryLT;
						writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lexTable, entryLT);
						findSameID = true;
						break;
					}
				}
				if (findSameID)	// если был найден такой же
				{
					continue;
				}

				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lexTable, entryLT);
				entryIT.idType = IT::L;
				entryIT.idDataType = IT::USHORT;
				entryIT.value.number = value;
				entryIT.idxfirstLE = indexLex;	//номер в табл лексем
				_itoa_s(countLit++, charCountLit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charCountLit) 

				// формирование имени литерала
				_mbscpy(bufL, L);	// помещаем в буфер "L"
				word[i] = _mbscat(bufL, (unsigned char*)charCountLit);	// формируем имя для литерала
				_mbscpy(entryIT.id, word[i]);
				_mbscpy(entryIT.idRegion, word[i]);
				IT::Add(idTable, entryIT);
				continue;
			}

			FST::FST fstLiteralString(word[i], FST_STRLIT);
			FST::FST fstLiteralSymbol(word[i], FST_CHRLIT);

			if (FST::execute(fstLiteralString) || FST::execute(fstLiteralSymbol))
			{
				bool isChar = false;
				if (FST::execute(fstLiteralSymbol)) {
					isChar = true;
				}

				// запись значения
				int length = _mbslen(word[i]);

				for (int k = 0; k < length; k++)	// перезапись массива, убираем кавычки
					word[i][k] = word[i][k + 1];
				word[i][length - 2] = '\0';


				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lexTable, entryLT);
				_mbscpy(entryIT.value.vstr.str, word[i]);	// запись значиния строкового литерала

				entryIT.value.vstr.len = length - 2;		// запись длины строкового литерала
				entryIT.idType = IT::L;
				entryIT.idDataType = IT::STR;

				if (isChar) {
					entryIT.idDataType = IT::CHR;
				}

				entryIT.idxfirstLE = indexLex;
				// формирование имени литерала
				_itoa_s(countLit++, charCountLit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charCountLit)
				_mbscpy(bufL, L);	// помещаем в буфер "L"

				nameLiteral = _mbscat(bufL, (unsigned char*)charCountLit);	// формируем имя для литерала (L + charCountLit)
				_mbscpy(entryIT.id, nameLiteral);
				_mbscpy(entryIT.idRegion, nameLiteral);
				IT::Add(idTable, entryIT);
				continue;
			}


			FST::FST fstSemicolon(word[i], FST_SEMICOLON);
			if (FST::execute(fstSemicolon))
			{
				ADD_TO_LEX(LEX_SEMICOLON)
				continue;
			}

			FST::FST fstComma(word[i], FST_COMMA);
			if (FST::execute(fstComma))
			{
				ADD_TO_LEX(LEX_COMMA)
				continue;
			}

			FST::FST fstLeftBrace(word[i], FST_LEFTBRACE);
			if (FST::execute(fstLeftBrace))
			{
				ADD_TO_LEX(LEX_LEFTBRACE)
				continue;
			}

			FST::FST fstRightBrace(word[i], FST_BRACELET);
			if (FST::execute(fstRightBrace))
			{
				ADD_TO_LEX(LEX_RIGHTBRACE)
				continue;
			}

			FST::FST fstLeftThesis(word[i], FST_LEFTTHESIS);
			if (FST::execute(fstLeftThesis))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LEFTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				LT::Add(lexTable, entryLT);
				if (indexID != 0)
					if (idTable.table[indexID - 1].idType == IT::F)
						findParm = true;
				continue;
			}

			FST::FST fstRightThesis(word[i], FST_RIGHTTHESIS);
			if (FST::execute(fstRightThesis))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_RIGHTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;

				if (findParm && word[i + 1][0] != LEX_LEFTBRACE 
					&& word[i + 2][0] != LEX_LEFTBRACE 
					&& !checkBrace(word, i + 1))		// если не закрыли функцию

					_mbscpy(regionPrefix, oldRegionPrefix);		// возвращаем предыдущую обл. видимости
				
				findParm = false;
				LT::Add(lexTable, entryLT);
				continue;
			}

			FST::FST fstEqual(word[i], FST_EQUAL);
			if (FST::execute(fstEqual))
			{
				ADD_TO_LEX(LEX_EQUAL)
				continue;
			}

			FST::FST fstPlus(word[i], FST_PLUS);
			if (FST::execute(fstPlus))
			{
				ADD_TO_LEX(LEX_PLUS)
				continue;
			}

			FST::FST fstMinus(word[i], FST_MINUS);
			if (FST::execute(fstMinus))
			{
				ADD_TO_LEX(LEX_MINUS)
				continue;
			}

			if (word[i][0] == DIV) {
				line++;
				indexLex--;
				continue;
			}

			throw ERROR_THROW_IN(201, line, i);
		};


		if (mainFuncCount == 0)
		{
			throw ERROR_THROW_IN(500, 0, 0);
		}
		if (mainFuncCount > 1)
		{
			throw ERROR_THROW_IN(501, 0, 0);
		}

		/*for (auto node : varTable.nodes) {
			cout << node->name << " " << node->type << " " << node->value << " " << node->IntValue << "\n";
		}*/

		lex.idTable = idTable;
		lex.lexTable = lexTable;
		return lex;
	}

	bool checkBrace(unsigned char** word, int k)
	{
		while (word[k][0] == DIV)
		{
			k++;
		}
		
		return word[k][0] == LEX_LEFTBRACE;
	}
}