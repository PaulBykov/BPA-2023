#pragma once

#define ERROR_THROW(id) Error::geterror(id);
#define ERROR_THROW_IN(id,l,c) Error::geterrorin(id,l,c);

#define ERROR_ENTRY(id, m) {id,m,{-1,-1}}        
#define ERROR_MAXSIZE_MESSAGE 200                
#define ERROR_ENTRY_NODEF(id)	ERROR_ENTRY(id,"Неопределенная ошибка") 


#define ERROR_ENTRY_NODEF5(id)	ERROR_ENTRY_NODEF(id+0),ERROR_ENTRY_NODEF(id+1),ERROR_ENTRY_NODEF(id+2),ERROR_ENTRY_NODEF(id+3),\
								ERROR_ENTRY_NODEF(id+4)


#define ERROR_ENTRY_NODEF10(id) ERROR_ENTRY_NODEF5(id+0), ERROR_ENTRY_NODEF5(id+5)


#define ERROR_ENTRY_NODEF50(id) ERROR_ENTRY_NODEF10(id+0),ERROR_ENTRY_NODEF10(id+10),ERROR_ENTRY_NODEF10(id+20),ERROR_ENTRY_NODEF10(id+30),\
								ERROR_ENTRY_NODEF10(id+40)


#define ERROR_ENTRY_NODEF100(id) ERROR_ENTRY_NODEF10(id+0),ERROR_ENTRY_NODEF10(id+10),ERROR_ENTRY_NODEF10(id+20),ERROR_ENTRY_NODEF10(id+30),\
								ERROR_ENTRY_NODEF10(id+40),ERROR_ENTRY_NODEF10(id+50),ERROR_ENTRY_NODEF10(id+60),ERROR_ENTRY_NODEF10(id+70),\
								ERROR_ENTRY_NODEF10(id+80),ERROR_ENTRY_NODEF10(id+90)
#define ERROR_MAX_ENTRY 500


#define LEX_SUCCESS "[Лексический анализ]      Успех \n"
#define SEM_SUCCESS "[Семантический анализ]    Успех \n"
#define SIN_SUCCESS "[Синтаксический анализ]   Успех \n"

#define WRITE_MSG_STATUS(destination) if (error.inext.line == -1) { destination << "Ошибка " << error.id << "\n" << error.message << "\n";} \
else { destination << "Ошибка " << error.id << "\tстрока " << error.inext.line << "\tпозиция " << error.inext.col << ": \n" << error.message << "\n";}


namespace Error
{
	struct ERROR
	{
		int id;									//код ошибки
		char message[ERROR_MAXSIZE_MESSAGE];    //сообщение об ошибке
		struct IN
		{
			short line;      //Номер строки
			short col;		 //номер позиции в сроке
		}inext;
	};

	ERROR geterror(int id);						 // ERROR_THROW
	ERROR geterrorin(int id, int line, int col); // ERROR_THROW_IN
};