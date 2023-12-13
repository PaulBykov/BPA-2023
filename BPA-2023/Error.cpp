#include "stdafx.h"
namespace Error
{
	/*����� ������   0-99		 ��������� ������
					 100-109	 ������ ����������
					 110-119	 ������ �������� � ������ ������
	*/

	ERROR errors[ERROR_MAX_ENTRY] = 
	{
		ERROR_ENTRY(0,"[���������] ������������ ��� ������"), //��� ������ ��� ��������� 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1,"[���������] ��������� ����"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF5(5),ERROR_ENTRY_NODEF50(10), ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"[���������] �������� -in ������ ���� �����"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"[���������] ��������� ������ �������� ���������"),
		ERROR_ENTRY_NODEF5(105),
		ERROR_ENTRY(110,"[���������] ������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111,"[���������] ������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112,"[���������] ������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY(113,"[���������] ������ ��� �������� ��������� ����� (-out)"),
		ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF5(115),
		ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
	
		ERROR_ENTRY(200,"[�����������] ������� ����������"),
		ERROR_ENTRY(201	,"[�����������] ������ ������������ �������"),
		ERROR_ENTRY(202,"[�����������] ����� �������������� ������ 8"),
		ERROR_ENTRY(203,"[�����������] ������������� �� ��������"),
		ERROR_ENTRY(204,"[�����������] ������, ������������ ������ ������� ��������������� 4096"),
		ERROR_ENTRY(205,"[�����������] ������� ��������������� �����������"),
		ERROR_ENTRY(206,"[�����������] ������, ������������ ������ ������� ������ 4096"),
		ERROR_ENTRY(207,"[�����������] ������� ������ �����������"),
		ERROR_ENTRY(208,"[�����������] ������������ �������� ���� number 32767"),
		ERROR_ENTRY(209,"[�����������] �������� ������ symbol"),
		ERROR_ENTRY(210, "[�����������] ������������ ��������� �������� � ���� ������"),
		ERROR_ENTRY_NODEF5(211), ERROR_ENTRY_NODEF(216),ERROR_ENTRY_NODEF(217),ERROR_ENTRY_NODEF(218),ERROR_ENTRY_NODEF(219),
		ERROR_ENTRY_NODEF10(220),
		ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),ERROR_ENTRY_NODEF50(250), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400),

		ERROR_ENTRY(500,"[C������������] ��� ����� ����� main"),
		ERROR_ENTRY(501,"[C������������] ����� ����� ����� ����� main"),
		ERROR_ENTRY(502,"[C������������] ������������ �������� �� ������������� ���� �������"),
		ERROR_ENTRY(503,"[C������������] ���������� ���������� ������� ������ �����������"),
		ERROR_ENTRY(504,"[C������������] ������������ ��������� �� ������������� �������"),
		ERROR_ENTRY(505,"[C������������] �� ������������ ���������� ������������ ����������"),
		ERROR_ENTRY(506,"[C������������] ������ � ���������� ���������� �������"),
		ERROR_ENTRY(507,"[C������������] ������ � ���������� ������� compare()"),
		ERROR_ENTRY(508,"[C������������] ������������� �������� � ��� ������"),
		ERROR_ENTRY(509,"[C������������] ������ � ��������� ������� write()"),
		ERROR_ENTRY(510,"[C������������] ������ � ����������� ����������"),
		ERROR_ENTRY(511,"[C������������] ������ � ���������� ����� repeat()"),
		ERROR_ENTRY_NODEF(512),ERROR_ENTRY_NODEF(513),ERROR_ENTRY_NODEF(514),
		ERROR_ENTRY_NODEF5(515), ERROR_ENTRY_NODEF10(520), ERROR_ENTRY_NODEF10(530),
		ERROR_ENTRY_NODEF10(540), ERROR_ENTRY_NODEF50(550),

		ERROR_ENTRY(600,"[C�������������] �������� ��������� ���������"),
		ERROR_ENTRY(601,"[C�������������] ��������� ����������� � �������"),
		ERROR_ENTRY(602,"[C�������������] ������ � ���������"),
		ERROR_ENTRY(603,"[C�������������] ������ � ���������� �������"),
		ERROR_ENTRY(604,"[C�������������] ������ � ���������� ���������� �������"),
		ERROR_ENTRY(605,"[C�������������] ������ � �������"),
		ERROR_ENTRY(606,"[C�������������] ������ � ���������"),
		ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF50(650), ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		ERROR error_info;	
		error_info.id = id;

		if (id > 0 && id < ERROR_MAX_ENTRY)							// ����������� ���������
		{
			strcpy_s(error_info.message, errors[id].message);
			error_info.inext.col = -1;
			error_info.inext.line = -1;
		}
		else
		{
			strcpy_s(error_info.message, errors[0].message);
		}
		return error_info;
	}

	ERROR geterrorin(int id, int line, int col)
	{
		ERROR error_info;												//	�������� ��������� ������� ���� ����� �������
		if (id > 0 && id < ERROR_MAX_ENTRY)						// ��������� ���������
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