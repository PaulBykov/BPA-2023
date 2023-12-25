#include "stdafx.h"
namespace Error
{

	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0,"[Системная] Недопустимый код ошибки"), //код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1,"[Системная] Системный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF5(5),ERROR_ENTRY_NODEF50(10), ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100,"[Системная] Параметр -in должен быть задан"),

		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),

		ERROR_ENTRY(104,"[Системная] Превышена длинна входного параматра"),

		ERROR_ENTRY_NODEF5(105),

		ERROR_ENTRY(110,"[Системная] Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111,"[Системная] Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112,"[Системная] Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113,"[Системная] Ошибка при открытии выходного файла (-out)"),

		ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF5(115),
		ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),

		ERROR_ENTRY(200,"[Лексическая] Двойное объявление"),
		ERROR_ENTRY(201,"[Лексическая] Ошибка лексического анализа"),
		ERROR_ENTRY(202,"[Лексическая] Длина идентификатора больше 8"),
		ERROR_ENTRY(203,"[Лексическая] Идентификатор не определён"),
		ERROR_ENTRY(204,"[Лексическая] Ошибка, максимальный размер таблицы идентификаторов 4096"),
		ERROR_ENTRY(205,"[Лексическая] Таблица идентификаторов переполнена"),
		ERROR_ENTRY(206,"[Лексическая] Ошибка, максимальный размер таблицы лексем 4096"),
		ERROR_ENTRY(207,"[Лексическая] Таблица лексем переполнена"),
		ERROR_ENTRY(208,"[Лексическая] Максимальное значение типа number 32767"),
		ERROR_ENTRY(209,"[Лексическая] Превышен максимальный размер symbol"),

		ERROR_ENTRY_NODEF(210), ERROR_ENTRY_NODEF5(211), ERROR_ENTRY_NODEF(216),
		ERROR_ENTRY_NODEF(217),ERROR_ENTRY_NODEF(218),ERROR_ENTRY_NODEF(219),
		ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),
		ERROR_ENTRY_NODEF50(250),

		ERROR_ENTRY(300,"[Cинтаксическая] Неверная структура программы"),
		ERROR_ENTRY(301,"[Cинтаксическая] Ошибочная конструкция"),
		ERROR_ENTRY(302,"[Cинтаксическая] Ошибка в выражении"),
		ERROR_ENTRY(303,"[Cинтаксическая] Ошибка в параметрах функции"),
		ERROR_ENTRY(304,"[Cинтаксическая] Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(305,"[Cинтаксическая] Ошибка в условии"),


		ERROR_ENTRY_NODEF(306), ERROR_ENTRY_NODEF(307), ERROR_ENTRY_NODEF(308),ERROR_ENTRY_NODEF(309),
		ERROR_ENTRY_NODEF10(310), ERROR_ENTRY_NODEF10(320),ERROR_ENTRY_NODEF10(330),
		ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF50(350),

		ERROR_ENTRY(400,"[Cемантическая] Нет точки входа main"),
		ERROR_ENTRY(401,"[Cемантическая] Более одной точки входа main"),
		ERROR_ENTRY(402,"[Cемантическая] Возвращаемое значение не соответствует типу функции"),
		ERROR_ENTRY(403,"[Cемантическая] Количество параметров функции больше допустимого"),
		ERROR_ENTRY(404,"[Cемантическая] Передаваемые параметры не соответствуют функции"),
		ERROR_ENTRY(405,"[Cемантическая] Не соответсвует количество передаваемых параметров"),
		ERROR_ENTRY(406,"[Cемантическая] Ошибка в параметрах встроенной функции"),
		ERROR_ENTRY(407,"[Cемантическая] Ошибка в параметрах функции compare()"),
		ERROR_ENTRY(408,"[Cемантическая] Несовместимый оператор и тип данных"),
		ERROR_ENTRY(409,"[Cемантическая] Ошибка в параметре функции write()"),
		ERROR_ENTRY(410,"[Cемантическая] Ошибка в подключении библиотеки"),
		ERROR_ENTRY(411,"[Cемантическая] Ошибка в параметрах цикла repeat()"),
		ERROR_ENTRY(412,"[Cемантическая] Недопустимое сочитание литерала и типа данных"),
		ERROR_ENTRY(413,"[Cемантическая] Попытка изменить значение константы"),
		ERROR_ENTRY(414,"[Cемантическая] Попытка использования переменной без значения"),
		ERROR_ENTRY(415,"[Cемантическая] Значение константы не может зависеть от результата функции"),
		ERROR_ENTRY(416,"[Cемантическая] Попытка использования рекурсии"),

		ERROR_ENTRY_NODEF(417), ERROR_ENTRY_NODEF(418),
		ERROR_ENTRY_NODEF(419), ERROR_ENTRY_NODEF10(420), ERROR_ENTRY_NODEF10(430),
		ERROR_ENTRY_NODEF10(440), ERROR_ENTRY_NODEF50(450)
	};

	ERROR geterror(int id)
	{
		ERROR error_info;
		error_info.id = id;

		if (id > 0 && id < ERROR_MAX_ENTRY) {							// сравнивание диапазона
			strcpy_s(error_info.message, errors[id].message);
			error_info.inext.col = -1;
			error_info.inext.line = -1;
		}
		else {
			strcpy_s(error_info.message, errors[0].message);
		}
		return error_info;
	}

	ERROR geterrorin(int id, int line, int col)
	{
		ERROR error_info;												//	создание структуру которую надо будет вернуть
		if (id > 0 && id < ERROR_MAX_ENTRY)						// сравнение диапазона
		{
			error_info.id = id;
			error_info.inext.col = col;
			error_info.inext.line = line;
			strcpy_s(error_info.message, errors[id].message);
			return error_info;
		}
		else
		{
			error_info.id = 0;
			error_info.inext.col = -1;
			error_info.inext.line = -1;
			strcpy_s(error_info.message, errors[0].message);
			return error_info;
		}
	}
	;
};