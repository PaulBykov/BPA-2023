#pragma once
#define PARM_IN L"-in:"					//ключ для файла исходного кода
#define PARM_OUT L"-out:"				//ключ для файла объектного кода
#define PARM_LOG L"-log:"				//ключ для файла журнала
#define PARM_MAX_SIZE 300				//максимальная длина строки параметра
#define PARM_OUT_DEFAULT_EXT L".asm"	//расширение файла объектного кода по умолчанию
#define PARM_LOG_DEFAULT_EXT L".log"	//расширение файла протокола по умолчанию

namespace Parm		
{
	struct PARM
	{
		wchar_t in[PARM_MAX_SIZE];		//  in
		wchar_t out[PARM_MAX_SIZE];		//  out
		wchar_t log[PARM_MAX_SIZE];		//  log
	};

	PARM getparm(int argc, wchar_t* argv[]);
};