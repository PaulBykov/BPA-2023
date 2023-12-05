#include "stdafx.h"
namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM Input = { NULL, NULL, NULL, true }; //�������� ���������� ��������� ��� �������� ����������

		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE) //���� ����� ��������� ������ ������������
			{
				throw ERROR_THROW(104)
			}
			if (wcsstr(argv[i], PARM_IN)) // wcsstr(arcg, PARM_IN) ��������� �� ������� ������  PARM_IN � ������ arcg ���������� NULL ���� ������ �� �������
				wcscpy_s(Input.in, argv[i] + wcslen(PARM_IN));  //�������� � Input.in , ���� � ������ ����� (���������� argv , ������� � wcslen(PARM_IN)( ����� ������ PARM_IN))
			else if (wcsstr(argv[i], PARM_OUT))
				wcscpy_s(Input.out, argv[i] + wcslen(PARM_OUT));//�������� � Input.out , ���� � ������ ����� (���������� argv , ������� � wcslen(PARM_OUT)( ����� ������ PARM_OUT))
			else if (wcsstr(argv[i], PARM_LOG))
				wcscpy_s(Input.log, argv[i] + wcslen(PARM_LOG));//�������� � Input.log , ���� � ������ ����� (���������� argv , ������� � wcslen(PARM_LOG)( ����� ������ PARM_LOG))
		}
		if (wcslen(Input.in) == 0) //���� �������� -in: �� �����
			throw ERROR_THROW(100);
		if (wcslen(Input.out) == 0)
		{
			wcscpy_s(Input.out, Input.in);//����������� � ������ Input.out ������ Input.in
			wcsncat_s(Input.out, PARM_OUT_DEFAULT_EXT, wcslen(PARM_OUT_DEFAULT_EXT)); // ���������� wcslen(PARM_OUT_DEFAULT_EXT) �������� ������ PARM_OUT_DEFAULT_EXT � Input.out
		}
		if (wcslen(Input.log) == 0)
		{
			wcscpy_s(Input.log, Input.in);//����������� � ������ Input.log ������ Input.in
			wcsncat_s(Input.log, PARM_LOG_DEFAULT_EXT, wcslen(PARM_LOG_DEFAULT_EXT)); // ���������� wcslen(PARM_OUT_DEFAULT_EXT) �������� ������ PARM_OUT_DEFAULT_EXT � Input.out
		}
		return Input;
	}
}