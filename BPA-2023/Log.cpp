#include "stdafx.h"
namespace Log
{

	LOG getlog(wchar_t logfile[])
	{
		LOG temp;
		temp.stream = new std::ofstream(logfile);
		if (!temp.stream->is_open())
			throw ERROR_THROW(112);
		wcscpy_s(temp.logfile, logfile);
		return temp;
	}

	void WriteLine(LOG log, const char* c, ...)
	{
		const char** ptr = &c;
		while (strlen(*ptr))
		{
			*log.stream << *ptr;
			++ptr;
		}
		*log.stream << std::endl;
	}

	void WriteLine(LOG log, const wchar_t* c, ...)

	{
		const wchar_t** ptr = &c;
		while (wcslen(*ptr))
		{
			char out[PARM_MAX_SIZE];
			size_t charsConverted = 0;								//функция преобразовавающая wchar_t* в char
			wcstombs_s(&charsConverted, out, *ptr, PARM_MAX_SIZE);	//Преобразует последовательность расширенных символов в соответствующую  последовательность многобайтовых символов
			// 1-ый аргумент: Размер в байтах преобразованной строки, включая нулевой терминатор 2-
			*log.stream << out;										// запись в файл параметра	
			++ptr;
		}
		*log.stream << std::endl;
	}

	void WriteLog(LOG log)
	{
		time_t  t = time(nullptr);
		tm  now;
		localtime_s(&now, &t);
		char date[PARM_MAX_SIZE];
		strftime(date, PARM_MAX_SIZE, "%d.%m.%Y %H:%M:%S", &now);
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		*log.stream << "---- Параметры -------" << std::endl;
		char out[PARM_MAX_SIZE];
		size_t charsConverted(0);
		wcstombs_s(&charsConverted, out, parm.log, PARM_MAX_SIZE);
		*log.stream << "-log: " << out << std::endl;
		wcstombs_s(&charsConverted, out, parm.out, PARM_MAX_SIZE);
		*log.stream << "-out: " << out << std::endl;
		wcstombs_s(&charsConverted, out, parm.in, PARM_MAX_SIZE);
		*log.stream << "-in: " << out << std::endl;
	}

	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "---- Исходные данные -----" << std::endl;
		*log.stream << "Количество символов: " << in.size << std::endl;
		*log.stream << "Проигнорировано:     " << in.ignor << std::endl;
		*log.stream << "Количество строк:    " << in.lines << std::endl;
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		if (log.stream == nullptr || !log.stream->is_open())
		{
			WRITE_MSG_STATUS(cout);
		}
		else
		{
			WRITE_MSG_STATUS(*log.stream);
		}
	}

	void Close(LOG log)//Используется для закрытия выходного потока протокола.
	{
		if (log.stream != nullptr)									//если поток открыт
		{
			log.stream->close();
			delete log.stream;
		}
	}

}