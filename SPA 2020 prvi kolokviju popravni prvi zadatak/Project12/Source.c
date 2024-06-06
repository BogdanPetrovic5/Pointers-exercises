#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void correctWord(char **word, int j, int i) {
	if (i <= j) {
		char temp = (*word)[i];
		(*word)[i] = (*word)[j];
		(*word)[j] = temp;
		correctWord(word, j - 1, i + 1);
	}
}
int main() {

	char c;
	int wordLength = 0;
	char* singleWord = (char*)malloc(32);
	while ((c = getchar()) != '\n') {
		if (c != ' ' && c != '?' && c != '.' && c != '!' && c != ',') {
			singleWord[wordLength] = c;
			wordLength += 1;
			singleWord[wordLength] = '\0';


		}
		else if (wordLength > 0 && isupper(singleWord[wordLength - 1])) {
			correctWord(&singleWord, wordLength - 1, 0);
			printf(singleWord);
			singleWord = (char*)malloc(32);
			wordLength = 0;
			putchar(c);
		}
		else if (wordLength > 0) {
			printf("%s", singleWord);
			putchar(c);
			singleWord = (char*)malloc(32);
			wordLength = 0;
		}
		else putchar(c);
		
	}

}