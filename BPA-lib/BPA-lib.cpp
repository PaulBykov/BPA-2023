#include <iostream>
#include <string.h>

extern "C" {
	void _printN(unsigned short a)
	{
		printf("%d\n", a);
	}

	void _printS(char str)
	{
		printf("%c\n", str);
	}

	unsigned short _compare(char* a, char* b)
	{
		if (strcmp(a, b) == 0)
		{
			printf("strings are equal");
			return 1;
		}

		if (strcmp(a, b) < 0)
		{
			printf("strings are not equal");
			return 0;
		}

		if (strcmp(a, b) > 0)
		{
			printf("strings are not equal");
			return 2;
		}

		return -1;
	}

	void _pause() {
		system("pause");
	}
}
