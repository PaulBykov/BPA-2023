#include "stdafx.h"
#include <queue>
#include "ConstValuecalculator.h"

namespace Sem
{
	bool Sem::checkSemantic(Lex::LEX& tables, Log::LOG& log)
	{
		int inlinePosition = 0;
		int prevNumOfStr = 0;


		for (int i = 0; i < tables.lexTable.size; i++) {
			IT::IDDATATYPE dataTypeLeftOp;
			IT::IDDATATYPE dataTypeRightOp;


			if (prevNumOfStr < tables.lexTable.table[i].numOfString) {
				inlinePosition = 0;
				prevNumOfStr = tables.lexTable.table[i].numOfString;
			}

			inlinePosition++;

			switch (tables.lexTable.table[i].lexema) {
			case LEX_INCLUDE:
			{
				if (tables.lexTable.table[++i].lexema == LEX_LITERAL) {
					if (CURR_ID.idDataType == IT::STR) {
						break;
					}
				}

				throw ERROR_THROW_IN(410, tables.lexTable.table[i].numOfString, inlinePosition); //ошибка при подключении библиотееи
			}
			case LEX_EQUAL:
			{
				if (PREV_ID.idType == IT::CONST && PREV_ID.defined) {
					throw ERROR_THROW_IN(413, i, inlinePosition);
				}

				if (NEXT_ID.idType == IT::LIB
					|| (NEXT_ID.idType == IT::PARM || PREV_ID.idType == IT::PARM)) {
					PREV_ID.defined = true;
					continue;
				}

				if (PREV_ID.idDataType != NEXT_ID.idDataType) {
					throw ERROR_THROW_IN(412, i, inlinePosition);
				}

				// расчет значений на этапе компиляции
				{
					string expr;
					bool isThereStr = false;

					int j = i + 1;
					while (tables.lexTable.table[j].lexema != LEX_SEMICOLON) {
						if (tables.lexTable.table[j].lexema == LEX_ID
							|| tables.lexTable.table[j].lexema == LEX_POW
							|| tables.lexTable.table[j].lexema == LEX_COMPARE)
						{
							auto current = tables.idTable.table[tables.lexTable.table[j].indexIT];

							if (current.idType == IT::FUNC || current.idType == IT::LIB) {
								if (PREV_ID.idType == IT::CONST) {
									throw ERROR_THROW_IN(415, tables.lexTable.table[i].numOfString, inlinePosition);
								}

								break;
							}
						}

						if (tables.lexTable.table[j].lexema == LEX_LITERAL || tables.lexTable.table[j].lexema == LEX_ID) {
							auto current = tables.idTable.table[tables.lexTable.table[j].indexIT];

							if (current.idDataType == IT::NUM || current.idDataType == IT::BOOL) {
								expr += to_string(get<short>(current.value));
							}
							else {
								expr = get<string>(current.value);

								isThereStr = true;
								break;
							}
						}
						else {
							if (tables.lexTable.table[j].lexema == LEX_PLUS) {
								expr.push_back('+');
							}
							else {
								expr.push_back('-');
							}
						}

						j++;
					}

					if (isThereStr == true) {
						PREV_ID.value = expr;
					}
					else {
						PREV_ID.value = calculateExpression(expr);
					}


				}

				PREV_ID.defined = true;

				break;
			}
			case LEX_PLUS:
			{
				if (tables.lexTable.table[i - 1].lexema == LEX_RIGHTTHESIS) {
					int k = i - 1;
					while (tables.lexTable.table[k].lexema != LEX_LEFTTHESIS) {
						k--; // ищем сам id ответсвенный за вызов функции
					}
					dataTypeLeftOp = tables.idTable.table[tables.lexTable.table[k - 1].indexIT].idDataType;
				}
				else {
					dataTypeLeftOp = PREV_ID.idDataType;
				}

				dataTypeRightOp = NEXT_ID.idDataType;


				if (!(dataTypeLeftOp == IT::NUM && dataTypeRightOp == IT::NUM)) {
					throw ERROR_THROW_IN(408, tables.lexTable.table[i].numOfString, inlinePosition);
				}

				break;
			}
			case LEX_MINUS:
			{
				if (tables.lexTable.table[i - 1].lexema == LEX_RIGHTTHESIS) {
					int k = i - 1;
					while (tables.lexTable.table[k].lexema != LEX_LEFTTHESIS) {
						k--; // ищем сам id ответсвенный за вызов функции
					}
					dataTypeLeftOp = tables.idTable.table[tables.lexTable.table[k - 1].indexIT].idDataType;
				}
				else {
					dataTypeLeftOp = PREV_ID.idDataType;
				}


				dataTypeRightOp = NEXT_ID.idDataType;


				if (!(dataTypeLeftOp == IT::NUM && dataTypeRightOp == IT::NUM)) {
					throw ERROR_THROW_IN(408, tables.lexTable.table[i].numOfString, inlinePosition);
				}
				break;

			}
			case LEX_WRITE:
			{
				i++;

				if (tables.lexTable.table[i++].lexema == LEX_LEFTTHESIS) {
					if ((CURR_ID.idType == IT::VAR || CURR_ID.idType == IT::CONST || CURR_ID.idType == IT::LIT)) {
						break;
					}
				}


				throw ERROR_THROW_IN(409, tables.lexTable.table[i].numOfString, inlinePosition);

			}
			case LEX_LOGICAL: // проверка логический операторов
			{
				dataTypeLeftOp = PREV_ID.idDataType;
				dataTypeRightOp = NEXT_ID.idDataType;


				if (!(dataTypeLeftOp == IT::NUM && dataTypeRightOp == IT::NUM)
					&& !(dataTypeLeftOp == IT::BOOL && dataTypeRightOp == IT::BOOL))
				{
					throw ERROR_THROW_IN(408, tables.lexTable.table[i].numOfString, inlinePosition);
				}

				break;
			}
			case LEX_COMPARE:
			{
				int paramsCount = 0;

				for (int j = i + 2; tables.lexTable.table[j].lexema != LEX_RIGHTTHESIS; j++)
				{
					if (tables.lexTable.table[j].lexema == LEX_ID || tables.lexTable.table[j].lexema == LEX_LITERAL)
					{
						paramsCount++;
						IT::IDDATATYPE ctype = tables.idTable.table[tables.lexTable.table[j].indexIT].idDataType;

						if (ctype != IT::STR) {
							throw ERROR_THROW_IN(407, tables.lexTable.table[i].numOfString, inlinePosition);
						}

					}
				}

				if (paramsCount != 2) {
					throw ERROR_THROW_IN(407, tables.lexTable.table[i].numOfString, inlinePosition);
				}

				break;
			}
			case LEX_REPEAT:
			{
				int paramsCount = 0;
				for (int j = i + 2; tables.lexTable.table[j].lexema != LEX_RIGHTTHESIS; j++)
				{
					if (tables.lexTable.table[j].lexema == LEX_ID || tables.lexTable.table[j].lexema == LEX_LITERAL)
					{
						paramsCount++;
						IT::IDDATATYPE ctype = tables.idTable.table[tables.lexTable.table[j].indexIT].idDataType;

						if (ctype != IT::NUM) {
							throw ERROR_THROW_IN(411, tables.lexTable.table[i].numOfString, inlinePosition);
						}

					}
				}

				if (paramsCount != 1) {
					throw ERROR_THROW_IN(411, tables.lexTable.table[i].numOfString, inlinePosition);
				}

				break;

			}
			case LEX_ID:
			{
				IT::Entry tmp = CURR_ID;

				if (tables.lexTable.table[i - 1].lexema != LEX_BOOL // любой тип
					&& tables.lexTable.table[i + 1].lexema != LEX_EQUAL) {  // если пытаемся записать значение
					if (tmp.idType == IT::VAR) {
						if (!tmp.defined) {
							throw ERROR_THROW_IN(414, tables.lexTable.table[i].numOfString, inlinePosition);
						}
					}
				}


				if (i > 0 && tables.lexTable.table[i - 1].lexema == LEX_FUNCTION)
				{
					if (tmp.idType == IT::FUNC) {
						for (int k = i + 1; k != tables.lexTable.size; k++)
						{
							char l = tables.lexTable.table[k].lexema;
							if (l == LEX_LEFTTHESIS) {
								int t = k;
								char lit = l;

								int paramCount = 0;

								do {
									t++;
									lit = tables.lexTable.table[t].lexema;

									if (lit == LEX_ID) {
										paramCount++;
									}

								} while (lit != LEX_RIGHTTHESIS && t < tables.lexTable.size);

								if (paramCount > PARAMS_MAX) {
									throw ERROR_THROW_IN(403, tables.lexTable.table[k].numOfString, inlinePosition);
								}
							}

							if (l == LEX_RETURN)
							{
								int lexAfterReturn = tables.lexTable.table[k + 1].indexIT; // след. за return
								if (lexAfterReturn != TI_NULLIDX)
								{
									// тип функции и возвращаемого значения не совпадают
									if (tables.idTable.table[lexAfterReturn].idDataType != tmp.idDataType) {
										throw ERROR_THROW_IN(402, tables.lexTable.table[k].numOfString, inlinePosition);
									}
								}
								break;
							}
						}
					}
				}
				if (tables.lexTable.table[i + 1].lexema == LEX_LEFTTHESIS && tables.lexTable.table[i - 1].lexema != LEX_FUNCTION) // вызов
				{
					if (tmp.idType == IT::FUNC)
					{
						std::queue<LT::Entry> queue;

						int protoParamsCount = 0;

						for (int iterator = tmp.indexLT + 1; tables.lexTable.table[iterator].lexema != LEX_RIGHTTHESIS; iterator++)
						{
							if (tables.lexTable.table[iterator].lexema == LEX_ID) {
								protoParamsCount++;
								queue.push(tables.lexTable.table[iterator]);
							}
						}

						if (protoParamsCount > PARAMS_MAX)
							throw ERROR_THROW_IN(403, tables.lexTable.table[i].numOfString, inlinePosition);

						// проверка передаваемых параметров
						for (int j = i + 1; tables.lexTable.table[j].lexema != LEX_RIGHTTHESIS; j++) {
							// проверка соответствия передаваемых параметров прототипам
							if (tables.lexTable.table[j].lexema == LEX_ID || tables.lexTable.table[j].lexema == LEX_LITERAL) {
								IT::IDDATATYPE ctype = tables.idTable.table[tables.lexTable.table[j].indexIT].idDataType;

								if (!queue.empty()) {
									if (ctype != tables.idTable.table[queue.front().indexIT].idDataType) {
										// Несовпадение типов передаваемых параметров
										throw ERROR_THROW_IN(404, tables.lexTable.table[i].numOfString, inlinePosition);
									}
									queue.pop();
								}
								else
								{
									// Количество передаваемых и принимаемых параметров не совпадает
									throw ERROR_THROW_IN(405, tables.lexTable.table[i].numOfString, inlinePosition);
								}
							}
						}
						if (!queue.empty())
						{
							throw ERROR_THROW_IN(405, tables.lexTable.table[i].numOfString, inlinePosition);
						}
					}
				}


				char prevLex = tables.lexTable.table[i - 1].lexema;

				if (tmp.indexLT == i && prevLex != LEX_NUMBER && prevLex != LEX_STRING && prevLex != LEX_FUNCTION)
				{
					throw ERROR_THROW_IN(203, tables.lexTable.table[i].numOfString, inlinePosition);
				}

				break;
			}

			}
		}
		return true;
	}
}