#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int value;
	struct Node* left; 
	struct Node* right;
}Node;
void printTree(Node* root, int space) {
	int COUNT = 5;  

	if (root == NULL) {
		return;
	}

	
	space += COUNT;


	printTree(root->right, space);


	printf("\n");
	for (int i = COUNT; i < space; i++) {
		printf(" ");
	}
	printf("%d\n", root->value);


	printTree(root->left, space);
}
Node* add(Node* root, int value) {
	Node* temp1, * temp2, * newNode;
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("Error while allocatiign memory!");
	}

	newNode->value = value;
	newNode->left = newNode->right = NULL;

	if (root == NULL) {
		root = newNode;
	}
	else {
		temp1 = root;
		while (temp1 != NULL) {
			temp2 = temp1;
			if (value < temp1->value) {
				temp1 = temp1->left;
			}
			else temp1 = temp1->right;
		}
		if (value < temp2->value) {
			temp2->left = newNode;
		}
		else temp2->right = newNode;

	}
	return root;
}


Node* findMin(Node* current) {
	while (current->left != NULL) {
		current = current->left;

	}
	return current;
}
Node* removeNode(Node* root, int value) {
	
	Node* currentNode = root;
	Node* parentNode = NULL;

	while (currentNode != NULL && currentNode->value != value) {
		parentNode = currentNode;
		if (currentNode->value > value) {
			currentNode = currentNode->left;
		}
		else currentNode = currentNode->right;
	}
	
	//Ako je cvor list
	if (currentNode->left == NULL && currentNode->right == NULL) {
		if (parentNode == NULL) {
			free(currentNode);
			return NULL;
		}
		if (currentNode != NULL && parentNode != NULL) {
			if (currentNode->value > parentNode->value) {
				parentNode->right = NULL;
			}
			else parentNode->left = NULL;

			free(currentNode);
			return root;
		}
	}
	//Ako ima jedno dete

	if (currentNode->left == NULL || currentNode->right == NULL) {
		Node* child = (currentNode->left == NULL) ? currentNode->right : currentNode->left;
		//Provera da li je cvor 
		if (parentNode == NULL && child == NULL) {
			free(currentNode);
			return NULL;
		}else if (parentNode == NULL && child != NULL) {
			free(currentNode);
			return child;
		}else if (currentNode->value < parentNode->value) {
			parentNode->left = child;
		}
		else parentNode->right = child;

		free(currentNode);
		
	}
	else {
		Node* successor = findMin(currentNode->right);
		int successorData = successor->value;
		if (currentNode->right != NULL) {
			currentNode->right = removeNode(currentNode->right, successor->value);
		}
		else currentNode->left = removeNode(currentNode->left, successor->value);
		
		currentNode->value = successorData;
	}

	return root;
}

//16 8 24 4 12 20 28 2 6 10 14 18 22 26 30 1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31
int count(Node *root) {
	if (root == NULL) return 0;
	else if (root->left == NULL && root->right == NULL) {
		return 1;
	}
	else {
		return (1 + count(root->left) + count(root->right));
	}
}
int main() {
	Node* root = NULL;
	int i, n, value;

	printf("Enter number of nodes: ");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &value);
		root = add(root, value);
	}
	int space = 0;
	printTree(root, space);
	printf("\n\n\n--------");
	
	
	int remove = 14;
	//Node* current = findValue(root, value);
	root = removeNode(root, remove);
	printf("Prvi poziv: \n\n\n--------");
	printTree(root, space);

	
	//remove = 9;
	//root = removeNode(root, remove);
	//printf("Drugi poziv: \n\n\n--------");
	//printTree(root, space);


	/*remove = 12;
	root = removeNode(root, remove);
	printf("Treci poziv: \n\n\n--------");
	printTree(root, space);



	remove = 13;
	root = removeNode(root, remove);
	printf("Cetvrti poziv: \n\n\n--------");
	printTree(root, space);

	remove = 14;
	root = removeNode(root, remove);
	printf("Cetvrti poziv: \n\n\n--------");
	printTree(root, space);

	remove = 15;
	root = removeNode(root, remove);
	printf("Cetvrti poziv: \n\n\n--------");
	printTree(root, space);*/

}