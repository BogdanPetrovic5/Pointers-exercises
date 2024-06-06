#include <string.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int toDec(int bin[], int n, int deg, int *num) {
    
    if (n >= 0) {
        *num = *num + pow(2, deg) * bin[n];
        toDec(bin, n - 1, deg + 1, num);
    }
    return 0;
}
int main() {
    char c;
    int* bin = (int*)malloc(sizeof(int) * 32);
    int counter = 0;
    int isDigit = 0;

    while ((c = getchar()) != '\n') {
       
        if (isdigit(c)) {
            bin[counter] = c - '0';
            counter += 1;
            isDigit = 1;
        }
        else {
            if(isDigit == 1){
                int num = 0;
                toDec(bin, counter - 1, 0, &num);
                printf("%d", num);
            }
	    free(bin);
            bin = (int*)malloc(sizeof(int) * 32);
            isDigit = 0;
            counter = 0;
            
            putchar(c);
        }
        
    }	
}