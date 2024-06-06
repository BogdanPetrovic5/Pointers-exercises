#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {
	int val;
	struct node* next;
}node;
int main() {
	int listElements;
	int counter = 0;
	printf("Enter num of elements: ");
	scanf("%d", &listElements);
	
	node* head = NULL;
	while (counter != listElements) {
		node* newNode = (node*)malloc(sizeof(node));
		scanf("%d", &newNode->val);
		newNode->next = head;
		head = newNode;
		counter += 1;
	}
	node* temp = head;
	printf("Loaded List: ");
	while (temp != NULL) {
		printf("%d ", temp->val);
		temp = temp->next;
	}
	node* firstList = NULL;
	node* secondList = NULL;
	counter = 0;
	while (head != NULL) {
		
		node* current = head;
		head = head->next;

		if (counter % 2 == 0) {
			if (firstList == NULL) {
				current->next = firstList;
				firstList = current;
			}
			else {
				temp = firstList;
				while (temp->next != NULL) {
					temp = temp->next;
				}
				current->next = temp->next;
				temp->next = current;
			}
			
		}
		else {
			if (secondList == NULL) {
				current->next = secondList;
				secondList = current;
			}
			else {
				temp = secondList;
				while (temp->next != NULL) {
					temp = temp->next;
				}
				current->next = temp->next;
				temp->next = current;
			}
		}
		counter += 1;
	}
	printf("\nFirst list: ");
	temp = firstList;
	while (temp != NULL) {
		printf("%d ", temp->val);
		temp = temp->next;
	}
	printf("\nSecond list: ");
	temp = secondList;
	while (temp != NULL) {
		printf("%d ", temp->val);
		temp = temp->next;
	}
}