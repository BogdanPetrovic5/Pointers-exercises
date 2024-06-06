#include <stdlib.h>
#include <stdio.h>
typedef struct Node {
	char c;
	struct Node* next;
}Node;
int main() {
	Node* head = NULL;
	int n;
	printf("Unesi n: ");
	scanf("%d", &n);
	int counter = 0;
	getchar();
	while (counter != n) {
		Node* newNode = (Node*)malloc(sizeof(Node));
		scanf("%c", &newNode->c);
		getchar();
		newNode->next = head;
		head = newNode;
		counter += 1;
	}
	printf("\n");
	Node* temp = head;
	while (temp != NULL) {
		printf("%c ", temp->c);
		temp = temp->next;
	}
	Node* newList = NULL;
	temp = head;
	Node* lastChar = NULL;
	
	while (temp != NULL) {
		Node* current = temp;
		if (temp->next == NULL) {
			break;
		}
		Node* lastChar = temp->next->next;
		temp = lastChar->next;
		
		if (current->c == lastChar->c) {
			if (newList == NULL) {
				newList = current;
				lastChar->next = NULL;

			}
			else {
				Node* newListTemp = newList;
				while (newListTemp->next != NULL) {
					newListTemp = newListTemp->next;
				}
				newListTemp->next = current;
				lastChar->next = NULL;
			}
		}
		
	}
	temp = newList;
	printf("\n");
	while (temp != NULL) {
		printf("%c", temp->c);
		temp = temp->next;
	}

}