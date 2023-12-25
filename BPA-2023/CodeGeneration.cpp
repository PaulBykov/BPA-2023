#include "stdafx.h"


#define ID_FROM_LEX_2 lex.idTable.table[lex.lexTable.table[i+2].indexIT]
#define ID_FROM_LEX_1 lex.idTable.table[lex.lexTable.table[i+1].indexIT]
#define ID_FROM_LEX_INC lex.idTable.table[lex.lexTable.table[i++].indexIT]
#define ID_FROM_LEX lex.idTable.table[lex.lexTable.table[i].indexIT]



namespace Gen
{

	void CodeGeneration(Lex::LEX& lex, wchar_t outfile[])
	{
		ofstream out(outfile);

		if (!out.is_open()) {
			throw ERROR_THROW(113);
		}

		string libPath;
		for (int i = 0; i < lex.lexTable.size && lex.lexTable.table[i].lexema != LEX_MAIN; i++)
		{
			if (lex.lexTable.table[i].lexema == LEX_INCLUDE)
			{
				libPath = get<string>(ID_FROM_LEX_1.value);
				break;
			}
		}


		// header
		out << ".586\n"
			<< ".model flat, stdcall\n"
			<< "\tincludelib libucrt.lib\n"
			<< "\tincludelib kernel32.lib";

		if (libPath.length() != 0)
			out << "\n\tincludelib " << libPath
			<< "\n\n\tEXTERN _printS :PROC\n\tEXTERN _printN :PROC\n\tEXTERN _pow :PROC\n\tEXTERN _compare :PROC\n\tEXTERN _pause :PROC";

		out << "\n\tExitProcess PROTO :DWORD\n";
		out << "\n.stack 4096\n";



		out << "\n.const\n";
		for (int i = 0; i < lex.idTable.size; i++)
		{
			const auto ID_ROW = lex.idTable.table[i];

			if (ID_ROW.idType == IT::LIT || ID_ROW.idType == IT::CONST)
			{
				out << "\t" << ID_ROW.idRegion;

				if (ID_ROW.idDataType == IT::STR || ID_ROW.idDataType == IT::CHR) {
					out << " BYTE '" << get<string>(ID_ROW.value) << "', 0\n";
				}

				if (ID_ROW.idDataType == IT::NUM || ID_ROW.idDataType == IT::BOOL) {
					out << " SWORD " << get<short>(ID_ROW.value) << endl;
				}
			}
		}

		out << "\n.data\n";
		for (int i = 0; i < lex.lexTable.size; i++)
		{
			if (lex.lexTable.table[i].lexema == LEX_VAR)
			{
				out << "\t" << ID_FROM_LEX_2.idRegion;

				if (ID_FROM_LEX_2.idDataType == IT::STR) {
					out << " DWORD 0\n";
				}

				if (ID_FROM_LEX_2.idDataType == IT::NUM || ID_FROM_LEX_2.idDataType == IT::BOOL) {
					out << " SWORD 0\n";
				}

				if (ID_FROM_LEX_2.idDataType == IT::CHR) {
					out << " BYTE 0\n";
				}


				i += 3;
			}
		}

		stack<IT::Entry> stack;


		int numberOfPoints = 0,
			numberOfRet = 0,
			numberOfEnds = 0;

		string funcName = "";

		bool flagFunc = false,
			flagRet = false,
			flagMain = false,
			flagIf = false,
			flagThen = false,
			flagElse = false,
			flagCycle = false,
			flagLibFunc = false;



		out << "\n.code\n";
		for (int i = 0; i < lex.lexTable.size; i++)
		{
			switch (lex.lexTable.table[i].lexema)
			{
			case LEX_FUNCTION:
			{
				funcName = (const char*)lex.idTable.table[lex.lexTable.table[++i].indexIT].idRegion;

				out << funcName << " PROC ";
				i += 2;

				for (; lex.lexTable.table[i].lexema != LEX_RIGHTTHESIS; i++)
				{
					if (lex.lexTable.table[i].lexema == LEX_ID || lex.lexTable.table[i].lexema == LEX_LITERAL)
					{
						if (ID_FROM_LEX.idType == IT::PARM)
						{
							out << ID_FROM_LEX.idRegion << " : ";

							if (ID_FROM_LEX.idDataType == IT::NUM || ID_FROM_LEX.idDataType == IT::BOOL) {
								out << "SWORD";
							}
							else if (ID_FROM_LEX.idDataType == IT::CHR) {
								out << "BYTE";
							}
							else {		// STR
								out << "DWORD";
							}
						}

						if (lex.lexTable.table[i + 1].lexema == LEX_COMMA) {
							out << ", ";
							i++;
						}
					}
				}

				flagFunc = true;
				out << endl;

				break;
			}
			case LEX_MAIN:
			{
				flagMain = true;
				out << "\nmain PROC\n";

				break;
			}
			case LEX_EQUAL:
			{
				int result_position = i - 1;

				if (lex.idTable.table[lex.lexTable.table[result_position].indexIT].idType == IT::CONST) {
					break;
				}


				while (lex.lexTable.table[i].lexema != LEX_SEMICOLON) {
					auto calculateFunc = [&]() {
						string tmpName;
						unsigned char lexema = lex.lexTable.table[i].lexema;
						bool isLib = false;

						switch (lexema) {
						case LEX_COMPARE:
						{
							tmpName = "_compare";
							i++;
							isLib = true;
							break;
						}
						case LEX_POW:
						{
							tmpName = "_pow";
							i++;
							isLib = true;
							break;
						}

						case LEX_ID:
						{
							tmpName = (const char*)ID_FROM_LEX_INC.idRegion;
							i++;
							break;
						}
						}

						for (; lex.lexTable.table[i].lexema != LEX_RIGHTTHESIS; i++)
						{
							if (lex.lexTable.table[i].lexema == LEX_ID || lex.lexTable.table[i].lexema == LEX_LITERAL) {
								stack.push(lex.idTable.table[lex.lexTable.table[i].indexIT]);
							}
						}


						while (!stack.empty()) {
							if (isLib) {
								out << "\tpush offset " << stack.top().idRegion << "\n";
							}
							else {
								out << "\t movzx eax, " << stack.top().idRegion << "\n";
								out << "\tpush eax" << "\n";
							}

							stack.pop();
						}

						out << "\tcall " << tmpName << "\n";
						out << "\t push eax" << "\n";
						};

					switch (lex.lexTable.table[i].lexema) {
					case LEX_COMPARE:
					case LEX_POW:
					case LEX_ID:
					{
						IT::IDTYPE type = lex.idTable.table[lex.lexTable.table[i].indexIT].idType;


						if (type == IT::FUNC || type == IT::LIB) {
							if (flagFunc && funcName == (const char*)lex.idTable.table[lex.lexTable.table[i].indexIT].idRegion) {
								throw ERROR_THROW_IN(416, lex.lexTable.table[i].numOfString, -1);
							}

							calculateFunc();
							break;
						}

						if (ID_FROM_LEX.idType == IT::VAR || ID_FROM_LEX.idType == IT::PARM) {
							out << "\tpush " << ID_FROM_LEX.idRegion << endl;
							break;
						}

						break;
					}
					case LEX_PLUS:
					{
						out << "\tpop ebx\n";

						i++;
						if (ID_FROM_LEX.idType == IT::FUNC || ID_FROM_LEX.idType == IT::LIB) {
							calculateFunc();
						}
						else {
							out << "\tpush " << ID_FROM_LEX.idRegion << "\n";
							out << "\tpop eax\n";
						}

						out << "\tadd ebx, eax \n";
						out << "\tpush ebx\n";

						break;
					}
					case LEX_MINUS:
					{
						out << "\tpop ebx\n";

						i++;
						if (ID_FROM_LEX.idType == IT::FUNC || ID_FROM_LEX.idType == IT::LIB) {
							calculateFunc();
						}
						else {
							out << "\tpush " << ID_FROM_LEX.idRegion << "\n";
							out << "\tpop eax\n";
						}

						out << "\tsub ebx, eax \n";
						out << "\tpush ebx\n";

						break;
					}
					case LEX_LITERAL:
					{
						if (lex.idTable.table[lex.lexTable.table[result_position].indexIT].idType == IT::CONST) {
							break; // игнорируем запись значения в константу
						}

						out << "\tpush ";

						if (ID_FROM_LEX.idDataType == IT::STR || ID_FROM_LEX.idDataType == IT::CHR) {
							out << "offset ";
						}

						out << ID_FROM_LEX.id << "\n";


						break;
					}
					}
					i++;
				}


				out << "\tpop " << lex.idTable.table[lex.lexTable.table[result_position].indexIT].idRegion << "\n";
				break;
			}
			case LEX_RETURN:
			{
				out << "\tpush ";
				i++;

				if (ID_FROM_LEX.idType == IT::LIT) {
					if (ID_FROM_LEX.idDataType == IT::NUM || ID_FROM_LEX.idDataType == IT::BOOL) {
						out << get<short>(ID_FROM_LEX_INC.value) << endl;
					}
					else {
						out << get<string>(ID_FROM_LEX_INC.value) << endl;
					}
				}
				else {
					out << ID_FROM_LEX_INC.idRegion << endl;
				}

				if (flagFunc || flagMain) {
					flagRet = true;
				}

				break;
			}
			case LEX_RIGHTBRACE:
			{
				if (flagMain && !flagThen && !flagElse && !flagFunc && !flagCycle)
				{
					if (flagRet) {
						flagRet = false;
					}

					if (libPath.length() != 0) {
						out << "\tcall _pause\n";
					}

					out << "\tcall ExitProcess\nmain ENDP\nend main";
				}

				if (flagFunc) {
					if (flagRet) {
						out << "\tpop eax\n\tret\n";
						out << funcName << " ENDP\n\n";
						flagFunc = false;		// ok?
						flagRet = false;
					}
				}

				if (flagThen) {
					flagThen = false;
					if (flagElse)
					{
						out << "\tjmp ife" << numberOfEnds << endl;
						flagElse = false;
					}
					out << "p" << numberOfPoints++ << ":\n";
				}

				if (flagElse) {
					flagElse = false;
					out << "ife" << numberOfEnds++ << ":\n";
				}

				if (flagCycle) {
					out << "loop " << "p" << numberOfPoints++ << "\n";
					flagCycle = false;
				}

				break;
			}
			case LEX_REPEAT:
			{
				flagCycle = true;

				// -----------------------------------------------------------------------------------------------------
				out << "\tmovzx ecx, " << ID_FROM_LEX_2.idRegion << endl;
				out << "p" << numberOfPoints << ":\n";
				break;
			}
			case LEX_IF:
			{
				flagIf = true;

				break;
			}
			case LEX_LEFTTHESIS:
			{
				if (flagIf)
				{
					if (lex.lexTable.table[i + 2].lexema == LEX_LOGICAL)
					{
						out << "\tmov ax, " << lex.idTable.table[lex.lexTable.table[i + 1].indexIT].idRegion << endl;
						out << "\tcmp ax, " << lex.idTable.table[lex.lexTable.table[i + 3].indexIT].idRegion << endl;


						auto LEXEMA = (string)(const char*)ID_FROM_LEX_2.id;

						struct components {
							string first;
							string second;
							string third;

							components() : first(""), second(""), third("") {}
							components(string a, string b, string c) {
								this->first = a;
								this->second = b;
								this->third = c;
							}
						};

						map<string, components> order = {
							{SEM_GREAT,			components("jg p", "jl p", "je p")},
							{SEM_LESS,			components("jl p", "jg p", "je p")},
							{SEM_EQUAL,			components("je p", "jg p", "jl p")},
							{SEM_GREATEQUAL,	components("je p", "jg p", "jl p")},
							{SEM_LESSEQUAL,		components("je p", "jl p", "jg p")},
							{SEM_NOTEQUAL,		components("jl p", "jg p", "je p")},
						};

						auto printInstructions = [&](components comp) {
							if (LEXEMA == SEM_EQUAL || LEXEMA == SEM_GREAT || LEXEMA == SEM_LESS) {
								out << "\t" << comp.first << numberOfPoints << endl;
								out << "\t" << comp.second << numberOfPoints + 1 << endl;
								out << "\t" << comp.third << numberOfPoints + 1 << endl;
							}
							else {
								out << "\t" << comp.first << numberOfPoints << endl;
								out << "\t" << comp.second << numberOfPoints << endl;
								out << "\t" << comp.third << numberOfPoints + 1 << endl;
							}
							};

						printInstructions(order[LEXEMA]);


						int j = i;
						while (lex.lexTable.table[j++].lexema != LEX_RIGHTBRACE)
						{
							while (lex.lexTable.table[j].lexema == DIV) {
								j++;
							}
							if (lex.lexTable.table[j + 2].lexema == LEX_ELSE)
							{
								flagElse = true;
								break;
							}

						}
					}
					flagThen = true;
					out << "p" << numberOfPoints++ << ":\n";
					flagIf = false;
					break;
				}

				break;
			}
			case LEX_ELSE:
			{
				flagElse = true;
				break;
			}
			case LEX_WRITE:
			{
				out << "\t mov ebx, ecx\n";
				out << "\tpush ";

				if (ID_FROM_LEX_2.idDataType == IT::NUM || ID_FROM_LEX_2.idDataType == IT::BOOL) {
					out << ID_FROM_LEX_2.idRegion;
					out << "\n\tcall _printN\n";
				}
				else {
					if (ID_FROM_LEX_2.idType == IT::LIT) {
						out << "offset " << ID_FROM_LEX_2.id;
					}
					else {
						if (ID_FROM_LEX_2.idType == IT::CONST) {
							out << "offset ";
						}

						out << ID_FROM_LEX_2.idRegion;
					}
					out << "\n\tcall _printS\n";
				}

				out << "\t mov ecx, ebx\n";
				break;
			}
			}
		}

		out.close();
	}
}