#include "ConstValuecalculator.h"


short calculateExpression(const std::string& expr) {
	int result = 0;
	int currentNumber = 0;
	char operation = '+';

	for (size_t i = 0; i < expr.length(); ++i) {
		char currentChar = expr[i];

		if (isdigit(currentChar)) {
			currentNumber = currentNumber * 10 + (currentChar - '0');
		}

		if (!isdigit(currentChar) && !isspace(currentChar) || i == expr.length() - 1) {
			if (operation == '+') {
				result += currentNumber;
			}
			else if (operation == '-') {
				result -= currentNumber;
			}

			operation = currentChar;
			currentNumber = 0;
		}
	}

	return result;
}