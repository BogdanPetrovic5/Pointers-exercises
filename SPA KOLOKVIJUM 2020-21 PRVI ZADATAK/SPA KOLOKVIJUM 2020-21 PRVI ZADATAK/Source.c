#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
void faktoriel(int num, int *fakt) {
	if (num >= 1) {
		*fakt *= num;
		faktoriel(num - 1, fakt);
	}
}
void calcDegree(int *wholeNumb, int degree, int originalNum) {
	if (degree > 1) {
		*wholeNumb = *wholeNumb * originalNum;
		calcDegree(wholeNumb, degree - 1, originalNum);
	}
}
int main() {
	char c;
	int flag = 0;
	int num;
	int wholeNumb = 0;
	int degree = 0;
	int noFakt = 0;
	while ((c = getchar()) != '\n') {
		if (flag == 1) {
			if (isdigit(c)) {
				num = c - '0';
				degree = (degree + num) * 10;
			}
			else {
				wholeNumb /= 10;
				int originalNum = wholeNumb;
				calcDegree(&wholeNumb, degree / 10, originalNum);
				printf("%d", wholeNumb);
				wholeNumb = 0;
				flag = 0;
			}
		}
		else if (isdigit(c)) {
			num = c - '0';
			wholeNumb = (wholeNumb + num) * 10;
		}
		else if (c == '!' && wholeNumb > 0) {
			int fakt = 1;
			faktoriel(wholeNumb / 10, &fakt);
			printf("%d", fakt);
			wholeNumb = 0;
			noFakt = 0;
		}
		else if (c == '^' && wholeNumb > 0) {
			flag = 1;
		}
		else if (wholeNumb > 0 && noFakt == 0) {
			printf("%d", wholeNumb/10);
			wholeNumb = 0;
			putchar(c);
			noFakt = 1;
		}
		else putchar(c);

	}
}