#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
void doTheMath(int first, int second, char op, int *result) {
	if (op == '+') {
		if (first != second) {
			(*result) = (*result) + 1;
			doTheMath(first + 1, second, op, result);
		}
	}
	if (op == '-') {
		if (first != second) {
			(*result) = (*result) + 1;
			doTheMath(first, second + 1, op, result);
		}
	}
	if (op == '*') {
		if (first != second) {
			(*result) = (*result) + 1;
			doTheMath(first, second - first, op, result);
		}
	}
}
int main() {
	char c;
	char op;
	int firstOperand = 0;
	int secondOperand = 0;
	int isSecondoperand = 0;
	while ((c = getchar()) != '\n') {
		if (isSecondoperand == 1) {
			if (isdigit(c)) {
				secondOperand += (c - '0');
				secondOperand *= 10;
			}
			else if (secondOperand != 0) {
				firstOperand /= 10;
				secondOperand /= 10;
				int result = 0;
				doTheMath(firstOperand, secondOperand, op, &result);
				if (op == '*') result += 1;
				printf("%d", result);
				putchar(c);
				firstOperand = 0;
				secondOperand = 0;
				isSecondoperand = 0;

			}

		}
		else if (isdigit(c)) {
			firstOperand += (c - '0');
			firstOperand *= 10;
		}
		else if (c == '*' || c == '+' || c == '-') {
			op = c;
		}
		else if (c == '=') {
			isSecondoperand = 1;
		}
		else if (c == 'x') {
			printf("x = ");
		}
		else if (secondOperand == 0 && firstOperand == 0) {
			putchar(c);
		}
	}
	
}