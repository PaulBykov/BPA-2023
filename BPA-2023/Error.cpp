#include "stdafx.h"
namespace Error
{

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
		ERROR_ENTRY(201,"[�����������] ������ ������������ �������"),
		ERROR_ENTRY(202,"[�����������] ����� �������������� ������ 8"),
		ERROR_ENTRY(203,"[�����������] ������������� �� ��������"),
		ERROR_ENTRY(204,"[�����������] ������, ������������ ������ ������� ��������������� 4096"),
		ERROR_ENTRY(205,"[�����������] ������� ��������������� �����������"),
		ERROR_ENTRY(206,"[�����������] ������, ������������ ������ ������� ������ 4096"),
		ERROR_ENTRY(207,"[�����������] ������� ������ �����������"),
		ERROR_ENTRY(208,"[�����������] ������������ �������� ���� number 32767"),
		ERROR_ENTRY(209,"[�����������] �������� ������������ ������ symbol"),

		ERROR_ENTRY_NODEF(210), ERROR_ENTRY_NODEF5(211), ERROR_ENTRY_NODEF(216),
		ERROR_ENTRY_NODEF(217),ERROR_ENTRY_NODEF(218),ERROR_ENTRY_NODEF(219),
		ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),
		ERROR_ENTRY_NODEF50(250),

		ERROR_ENTRY(300,"[C�������������] �������� ��������� ���������"),
		ERROR_ENTRY(301,"[C�������������] ��������� �����������"),
		ERROR_ENTRY(302,"[C�������������] ������ � ���������"),
		ERROR_ENTRY(303,"[C�������������] ������ � ���������� �������"),
		ERROR_ENTRY(304,"[C�������������] ������ � ���������� ���������� �������"),
		ERROR_ENTRY(305,"[C�������������] ������ � �������"),


		ERROR_ENTRY_NODEF(306), ERROR_ENTRY_NODEF(307), ERROR_ENTRY_NODEF(308),ERROR_ENTRY_NODEF(309),
		ERROR_ENTRY_NODEF10(310), ERROR_ENTRY_NODEF10(320),ERROR_ENTRY_NODEF10(330),
		ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF50(350),

		ERROR_ENTRY(400,"[C������������] ��� ����� ����� main"),
		ERROR_ENTRY(401,"[C������������] ����� ����� ����� ����� main"),
		ERROR_ENTRY(402,"[C������������] ������������ �������� �� ������������� ���� �������"),
		ERROR_ENTRY(403,"[C������������] ���������� ���������� ������� ������ �����������"),
		ERROR_ENTRY(404,"[C������������] ������������ ��������� �� ������������� �������"),
		ERROR_ENTRY(405,"[C������������] �� ������������ ���������� ������������ ����������"),
		ERROR_ENTRY(406,"[C������������] ������ � ���������� ���������� �������"),
		ERROR_ENTRY(407,"[C������������] ������ � ���������� ������� compare()"),
		ERROR_ENTRY(408,"[C������������] ������������� �������� � ��� ������"),
		ERROR_ENTRY(409,"[C������������] ������ � ��������� ������� write()"),
		ERROR_ENTRY(410,"[C������������] ������ � ����������� ����������"),
		ERROR_ENTRY(411,"[C������������] ������ � ���������� ����� repeat()"),
		ERROR_ENTRY(412,"[C������������] ������������ ��������� �������� � ���� ������"),
		ERROR_ENTRY(413,"[C������������] ������� �������� �������� ���������"),
		ERROR_ENTRY(414,"[C������������] ������� ������������� ���������� ��� ��������"),
		ERROR_ENTRY(415,"[C������������] �������� ��������� �� ����� �������� �� ���������� �������"),
		ERROR_ENTRY(416,"[C������������] ������� ������������� ��������"),

		ERROR_ENTRY_NODEF(417), ERROR_ENTRY_NODEF(418),
		ERROR_ENTRY_NODEF(419), ERROR_ENTRY_NODEF10(420), ERROR_ENTRY_NODEF10(430),
		ERROR_ENTRY_NODEF10(440), ERROR_ENTRY_NODEF50(450)
	};

	ERROR geterror(int id)
	{
		ERROR error_info;
		error_info.id = id;

		if (id > 0 && id < ERROR_MAX_ENTRY) {							// ����������� ���������
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