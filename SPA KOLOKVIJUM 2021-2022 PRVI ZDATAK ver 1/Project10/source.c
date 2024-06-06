// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
bool isPalindrom(char arr[], int i, int j) {
	if (i >= j) {
		return 1;
	}
	if (tolower(arr[i]) != tolower(arr[j])) {
		return 0;
	}
	isPalindrom(arr, i+1, j-1);
}
int main() {
	char* arr = (char*)malloc(32);
	char c;
	int counter = 0;
	while ((c = getchar()) != '\n') {
		if (c != ' ' && c != '.') {
			arr[counter] = c;
			counter += 1;
			
		}
		else {
			
			arr[counter] = '\0';
			int flag = isPalindrom(arr,0, counter -1);
		
			if (flag == 1) {
				for (int i = 0; i < counter; i++) {
					arr[i] = toupper(arr[i]);
				}
				
			}
			printf("%s", arr);
			putchar(c);
			free(arr);
			arr = (char*)malloc(32);
			counter = 0;
		}
		
	}
	arr[counter] = '\0';
	int flag = isPalindrom(arr, 0, counter - 1);

	if (flag == 1) {
		for (int i = 0; i < counter; i++) {
			arr[i] = toupper(arr[i]);
		}

	}
	printf("%s", arr);
	putchar(c);
	free(arr);
	
	
}