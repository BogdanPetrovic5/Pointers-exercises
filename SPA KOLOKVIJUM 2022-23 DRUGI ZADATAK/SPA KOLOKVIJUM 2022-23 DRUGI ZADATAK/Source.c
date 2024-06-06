#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <stdbool.h>
#include <string.h>
typedef struct node {
	char letter;
	struct node* next;
}node;

bool isVowel(char letter) {
	return letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u' ||
		letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U';
}
int main() {
	int numOfChar;
	int counter = 0;
	printf("Enter num of letters: ");
	scanf("%d", &numOfChar);
	getchar();
	node* head;
	node* firstLetter = (node*)malloc(sizeof(node));
	scanf("%c", &firstLetter->letter);
	
	firstLetter->next = NULL;
	head = firstLetter;
	counter += 1;
	getchar();
	while (counter != numOfChar) {
		node* newLetter = (node*)malloc(sizeof(node));
		node* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newLetter;
		newLetter->next = NULL;
		scanf("%c", &newLetter->letter);
		getchar();
		counter += 1;
		
	}
	

	node* temp = head;
	while (temp != NULL) {
		printf("%c ", temp->letter);
		temp = temp->next;
	}

	printf("\n");
	node* vowels = NULL;
	node* consonants = NULL;
	
	while (head != NULL) {
		node* current = head;
		head = head->next;
		int flag = 0;
		if (isVowel(current->letter)) {
			if (vowels != NULL) {
				temp = vowels;
				while (temp != NULL) {
					if (temp->letter == current->letter) flag = 1;
					temp = temp->next;
				}
			}
			if (flag != 1) {
				current->next = vowels;
				vowels = current;
			}
			
		}
		else {
			current->next = consonants;
			consonants = current;
		}
	}

	temp = vowels;
	
	while (temp != NULL) {
		printf("%c ", temp->letter);
		temp = temp->next;
	}
	printf("\n");
	temp = consonants;
	while (temp != NULL) {
		printf("%c ", temp->letter);
		temp = temp->next;
	}
}