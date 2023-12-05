#include "stdafx.h"

int _tmain(int argc, _TCHAR** argv)
{
	setlocale(LC_ALL, "Rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv); // передача и обработка параметров
		log = Log::getlog(parm.log);

		Log::WriteLog(log);			// Заголовок протокола
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		Lex::LEX lex = Lex::lexAnaliz(log, in); 

		//LT::show(lex.lexTable, parm);
		//IT::show(lex.idTable, parm);
		std::cout << LEX_SUCCESS;
		*log.stream << LEX_SUCCESS;



		/*MFST_TRACE_START*/
		MFST::Mfst mfst(lex, GRB::getGreibach(), parm.trace);

		mfst.start();										
		mfst.savededucation();

		if (!mfst.start())
			throw ERROR_THROW(600);

		std::cout << SIN_SUCCESS;
		*log.stream << SIN_SUCCESS;



		// mfst.printrules();
		if (Sem::checkSemantic(lex, log))
		{
			std::cout << SEM_SUCCESS;
			*log.stream << SEM_SUCCESS;
		}
		
		
		
		Gen::CodeGeneration(lex, parm.out);


		system("pause");
		Log::Close(log);
	}
	catch (Error::ERROR error)
	{
		Log::WriteError(log, error);
		std::cout << "Error on line: " << error.inext.line 
			<< " : " << error.id 
			<< ": " << error.message 
			<< "\n";
		
		system("pause");
	}

	return 0;
}