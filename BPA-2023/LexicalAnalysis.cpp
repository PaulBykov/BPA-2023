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


#define ADD_SIMPLE_LEX(FST_TYPE, LEX_TYPE) \
    { \
        FST::FST fst(word[i], FST_TYPE); \
        if (FST::execute(fst)) { \
            ADD_TO_LEX(LEX_TYPE); \
            continue; \
        } \
    }



using namespace std;

namespace Lex
{

	LEX lexAnaliz(Log::LOG log, In::IN in)
	{
		LEX lex;
		LT::LexTable lexTable = LT::Create(LT_MAXSIZE);
		IT::IdTable idTable = IT::Create(TI_MAXSIZE);

		unsigned char** word = new unsigned char* [MAX_WORDS];

		for (int i = 0; i < MAX_WORDS; i++) {
			word[i] = new unsigned char[WORD_SIZE] {NULL};
		}

		word = divideText(in);


		bool findFunction = false;
		bool findParm = false;
		bool findDeclaration = false;


		int indexLex = 0;
		int indexID = 0;
		int countLit = 1;
		int line = 1;
		int mainFuncCount = 0;
		int inlinePosition = 0;

		unsigned char emptystr[] = "";
		unsigned char* regionPrefix = new unsigned char[10] { "" };
		unsigned char* bufRegionPrefix = new unsigned char[10] { "" };
		unsigned char* oldRegionPrefix = new unsigned char[10] { "" };
		unsigned char* L = new unsigned char[2] { "L" };		// начальный символ для имён литералов + \0
		unsigned char* bufL = new unsigned char[TI_STR_MAXSIZE];
		unsigned char* nameLiteral = new unsigned char[TI_STR_MAXSIZE] { "" };

		char* charCountLit = new char[10] { "" };		// для строковой записи счетчика
		unsigned char* startWord = new unsigned char[WORD_SIZE] {NULL}; //для области видимости


		IT::Entry entryIT;


		for (int i = 0; word[i] != NULL; i++, indexLex++) {
			bool findSameID = false;
			inlinePosition++;

			ADD_SIMPLE_LEX(FST_SEMICOLON, LEX_SEMICOLON);

			ADD_SIMPLE_LEX(FST_LEFTBRACE, LEX_LEFTBRACE);

			ADD_SIMPLE_LEX(FST_RIGHTLET, LEX_RIGHTBRACE);

			FST::FST fstLeftThesis(word[i], FST_LEFTTHESIS);
			if (FST::execute(fstLeftThesis))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LEFTTHESIS, LT_TI_NULLIDX, line);
				entryLT.priority = 0;
				LT::Add(lexTable, entryLT);
				if (indexID != 0) {
					if (idTable.table[indexID - 1].idType == IT::FUNC) {
						findParm = true;
					}
				}

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


			ADD_SIMPLE_LEX(FST_EQUAL, LEX_EQUAL);

			ADD_SIMPLE_LEX(FST_PLUS, LEX_PLUS);

			ADD_SIMPLE_LEX(FST_MINUS, LEX_MINUS);

			FST::FST fstLogical(word[i], FST_LOGICAL);
			if (FST::execute(fstLogical))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LOGICAL, indexID++, line); //создание структуры
				LT::Add(lexTable, entryLT); //добавление структуры в таблицу
				_mbscpy(entryIT.id, word[i]);

				entryIT.indexLT = indexLex;
				entryIT.idType = IT::OP;
				IT::Add(idTable, entryIT);
				continue;
			}



			ADD_SIMPLE_LEX(FST_COMMA, LEX_COMMA);



			ADD_SIMPLE_LEX(FST_IF, LEX_IF);

			ADD_SIMPLE_LEX(FST_ELSE, LEX_ELSE);


			ADD_SIMPLE_LEX(FST_REPEAT, LEX_REPEAT);


			ADD_SIMPLE_LEX(FST_RETURN, LEX_RETURN);


			ADD_SIMPLE_LEX(FST_VAR, LEX_VAR);

			ADD_SIMPLE_LEX(FST_CONST, LEX_CONST);



			FST::FST fstTypeInteger(word[i], FST_NUMBER);
			if (FST::execute(fstTypeInteger))
			{
				ADD_TO_LEX(LEX_NUMBER);
				entryIT.idDataType = IT::NUM; //запись типа идентификатора в структуру

				findDeclaration = true;
				continue;
			}


			FST::FST fstTypeString(word[i], FST_STRING);
			if (FST::execute(fstTypeString))
			{
				ADD_TO_LEX(LEX_STRING);

				entryIT.idDataType = IT::STR;
				entryIT.value = std::string(reinterpret_cast<const char*>(emptystr));

				findDeclaration = true;
				continue;
			}


			FST::FST fstTypeSymbol(word[i], FST_SYMBOL);
			if (FST::execute(fstTypeSymbol))
			{
				//std::cout << "i = " << i << " word[i] = " << word[i] << " word[i+1] = " << word[i + 1] << "\t" << word[i + 2] << "\n";

				ADD_TO_LEX(LEX_SYMBOL);
				entryIT.idDataType = IT::STR;
				entryIT.value = std::string(reinterpret_cast<const char*>(emptystr));

				findDeclaration = true;
				continue;
			}


			FST::FST fstTypeBool(word[i], FST_BOOL);
			if (FST::execute(fstTypeBool))
			{
				ADD_TO_LEX(LEX_BOOL);
				entryIT.idDataType = IT::BOOL; //запись типа идентификатора в структуру

				findDeclaration = true;
				continue;
			}



			FST::FST fstFunction(word[i], FST_FUNCTION);
			if (FST::execute(fstFunction))
			{
				ADD_TO_LEX(LEX_FUNCTION);

				entryIT.idType = IT::FUNC;
				findFunction = true; //установка флага функции
				continue;
			}



			FST::FST fstPrint(word[i], FST_WRITE);
			if (FST::execute(fstPrint))
			{
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_WRITE, indexID++, line);
				LT::Add(lexTable, entryLT);

				entryIT.idType = IT::LIB;
				entryIT.indexLT = indexLex;

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

				entryIT.idType = IT::LIT;
				entryIT.idDataType = IT::BOOL;

				entryIT.value = short(1);
				if (word[i][0] == 'f') {		// если false
					entryIT.value = short(0);
				}

				entryIT.indexLT = indexLex;	//номер в табл лексем
				_itoa_s(countLit++, charCountLit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charCountLit) 

				// формирование имени литерала
				_mbscpy(bufL, L);	// помещаем в буфер "L"
				word[i] = _mbscat(bufL, (unsigned char*)charCountLit);	// формируем имя для литерала
				_mbscpy(entryIT.id, word[i]);
				_mbscpy(entryIT.idRegion, word[i]);
				IT::Add(idTable, entryIT);
				continue;
			}



			FST::FST fstLiteralInt(word[i], FST_INTLIT); //если литерал 
			if (FST::execute(fstLiteralInt))
			{
				short value;
				char* buf;
				if (atoi((char*)word[i]) > MAX_NUMBER) {
					throw ERROR_THROW_IN(208, line, inlinePosition);
				}



				value = atoi((char*)word[i]);

				for (int k = 0; k < idTable.size; k++) // поиск такого же
				{
					if (std::holds_alternative<short>(idTable.table[k].value)) {
						if (get<short>(idTable.table[k].value) == value && idTable.table[k].idType == IT::LIT)
						{
							LT::Entry entryLT;
							writeEntry(entryLT, LEX_LITERAL, k, line);
							LT::Add(lexTable, entryLT);
							findSameID = true;
							break;
						}
					}

				}
				if (findSameID)	// если был найден такой же
				{
					continue;
				}

				LT::Entry entryLT;
				writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lexTable, entryLT);
				entryIT.idType = IT::LIT;
				entryIT.idDataType = IT::NUM;
				entryIT.value = value;
				entryIT.indexLT = indexLex;	//номер в табл лексем
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

				entryIT.value = std::string(reinterpret_cast<const char*>(word[i]));	// запись значиния строкового литерала


				entryIT.idType = IT::LIT;
				entryIT.idDataType = IT::STR;

				if (isChar) {
					entryIT.idDataType = IT::CHR;
				}

				entryIT.indexLT = indexLex;

				// формирование имени литерала
				_itoa_s(countLit++, charCountLit, sizeof(char) * 10, 10);	// countLit в строку charCountLit 
				_mbscpy(bufL, L);

				nameLiteral = _mbscat(bufL, (unsigned char*)charCountLit);
				_mbscpy(entryIT.id, nameLiteral);
				_mbscpy(entryIT.idRegion, nameLiteral);
				IT::Add(idTable, entryIT);
				continue;
			}
			if (word[i][0] == '\'') {
				throw ERROR_THROW_IN(209, line, inlinePosition);
			}



			ADD_SIMPLE_LEX(FST_INCLUDE, LEX_INCLUDE);


			FST::FST fstIdentif(word[i], FST_ID);
			if (FST::execute(fstIdentif))
			{
				FST::FST fstLibPow(word[i], FST_LIB_POW);
				FST::FST fstLibCompare(word[i], FST_LIB_COMPARE);

				if (_mbslen(word[i]) >= ID_MAXSIZE) {
					throw ERROR_THROW_IN(202, line, inlinePosition);
				}

				_mbscpy(startWord, word[i]);


				if (findFunction)	// если функция
				{
					int idx = IT::IsIDRegion(idTable, word[i]);	// ищем без префикса
					if (idx != TI_NULLIDX)						// если такой идентификатор уже есть
					{
						if (lexTable.table[indexLex - 1].lexema == LEX_FUNCTION)
						{
							throw ERROR_THROW_IN(200, line, inlinePosition);
						}

						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lexTable, entryLT);

						findFunction = false;
						continue;
					}
				}
				else
				{
					int idx = IT::IsIDRegion(idTable, word[i]);
					if (idx != TI_NULLIDX)
					{
						if (lexTable.table[indexLex - 2].lexema == LEX_VAR
							|| lexTable.table[indexLex - 2].lexema == LEX_CONST)
						{
							throw ERROR_THROW_IN(200, line, inlinePosition);
						}


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
						if (lexTable.table[indexLex - 2].lexema == LEX_VAR
							|| lexTable.table[indexLex - 2].lexema == LEX_CONST)
						{
							throw ERROR_THROW_IN(200, line, inlinePosition);
						}


						LT::Entry entryLT;
						writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lexTable, entryLT);
						continue;
					}
				}
				LT::Entry entryLT;
				writeEntry(entryLT, LEX_ID, indexID++, line);

				if (findParm) {
					entryIT.idType = IT::PARM;
				}
				else if (!findFunction) {
					// если переменная
					if (findDeclaration)
					{
						entryIT.idType = IT::VAR;

						if (std::string(reinterpret_cast<const char*>(word[i - 2])) == "const") {
							entryIT.idType = IT::CONST;
						}

						if (entryIT.idDataType == IT::NUM || entryIT.idDataType == IT::BOOL)
						{
							entryIT.value = short(TI_INT_DEFAULT);
						}


						if (entryIT.idDataType == IT::STR || entryIT.idDataType == IT::CHR)
						{
							entryIT.value = TI_STR_DEFAULT;
						}

						findDeclaration = false;
					}
					else
					{
						FST::FST fstLibCompare(startWord, FST_LIB_COMPARE);

						if (FST::execute(fstLibCompare)) {
							entryLT.lexema = LEX_COMPARE;
							entryIT.idType = IT::LIB;
						}
						else {
							throw ERROR_THROW_IN(203, line, inlinePosition);
						}
					}
				}
				else {		// если функция
					_mbscpy(oldRegionPrefix, regionPrefix);
					_mbscpy(regionPrefix, word[i]);
				}

				LT::Add(lexTable, entryLT);
				entryIT.indexLT = indexLex;
				_mbscpy(entryIT.id, startWord);
				_mbscpy(entryIT.idRegion, word[i]);
				IT::Add(idTable, entryIT);
				findFunction = false;
				continue;
			}


			if (word[i][0] == DIV) {
				line++;
				indexLex--;
				inlinePosition = 0;
				continue;
			}

			throw ERROR_THROW_IN(201, line, inlinePosition);
		};


		if (mainFuncCount == 0) {
			throw ERROR_THROW_IN(500, -1, -1);
		}

		if (mainFuncCount > 1) {
			throw ERROR_THROW_IN(501, -1, -1);
		}


		lex.idTable = idTable;
		lex.lexTable = lexTable;
		return lex;
	}


	bool checkBrace(unsigned char** word, int k)
	{
		while (word[k][0] == DIV) {
			k++;
		}

		return word[k][0] == LEX_LEFTBRACE;
	}
}