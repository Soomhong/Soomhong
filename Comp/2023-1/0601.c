#include <stdio.h>
#include <stdlib.h>

typedef char element;

typedef struct treeNode{
	char key;
	struct treeNode* left;
	struct treeNode* right;
} treeNode;

treeNode* searchBST(treeNode* root, char x){
	treeNode* p;
	p = root;
	while (p != NULL){
		if (x < p -> key)p = p->left;
		else if (x == p -> key) return p;
		else p = p->right;
	}
	printf("\n None.");
	return p;
}

treeNode* insertNode(treeNode *p, char x){
	treeNode *newNode;
	if(p == NULL){
		newNode = (treeNode*)malloc(sizeof(treeNode));
		newNode -> key = x;
		newNode -> left = NULL;
		newNode -> right = NULL;
		return newNode;
	}
	else if (x < p -> key) p -> left = insertNode(p -> left, x);
	else if (x < p -> key) p -> right = insertNode(p -> right, x);
	else printf("\n The same key already exists.\n");
	
	return p;
}

void deleteNode(treeNode *root, element key){
	treeNode *parent, *p, *succ, *succ_parent;
	treeNode *child;
	parent = NULL;
	p = root;
	while((p != NULL) && (p -> key != key)) {
		parent = p;
		if (key < p ->key)p = p-> left;
		else p = p -> right;
	}
	
	if (p == NULL){
		printf("\n The key you are looking for does not exist in the binary tree.");
		return;
	}
	
	if((p -> left == NULL) && (p -> right == NULL)){
		if(parent != NULL){
			if(parent -> left == p) parent -> left == NULL;
			else parent -> right = NULL;
		}
		else root = NULL;
	}
	
	else if ((p -> left == NULL) || (p -> right == NULL)){
		if (p -> left != NULL) child = p -> left;
		else child = p -> right;
		
		if(parent != NULL){
			if (parent -> left == p) parent -> left = child;
			else parent -> right = child;
		}
		
		else root = child;
	}
	
	else {
		succ_parent = p;
		succ = p->left;
		while(succ -> right != NULL){
			succ_parent = succ;
			succ = succ -> right;
		}
		if(succ_parent -> left == succ) succ_parent -> left = succ -> left;
		else succ_parent -> right = succ -> left;
		p->key = succ->key;
		p = succ;
	}
	free(p);
}

void displayInorder(treeNode* root){
	if (root){
		displayInorder(root -> left);
		printf("%c_", root->key);
		displayInorder(root->right);
	}
}

void menu(){
	
	printf("\n*-----------------------------------*");
	printf("\nt1 : print");
	printf("\nt2 : inputt");
	printf("\nt3 : delete");
	printf("\nt4 : search");
	printf("\nt5 : end");
	printf("\n*-----------------------------------*");
	printf("\nmenu >>");
}


int main(){
	treeNode* root = NULL;
	treeNode* foundedNode = NULL;
	char choice, key;
	
	root = insertNode(root, 'G');
	insertNode(root, 'I');
	insertNode(root, 'H');
	insertNode(root, 'D');
	insertNode(root, 'B');
	insertNode(root, 'M');
	insertNode(root, 'N');
	insertNode(root, 'A');
	insertNode(root, 'J');
	insertNode(root, 'E');
	insertNode(root, 'Q');
	
	while(1){
		menu();
		scanf(" %c", &choice);
		
		switch (choice - '0'){
			case 1: printf("\t[printf Binary tree]");
				displayInorder(root); printf("\n");
				break;
				
			case 2: printf("input what you inserted: ");
				scanf(" %c", &key);
				insertNode(root, key);
				break;
				
			case 3: printf("input what you deleted: ");
				scanf(" %c", &key);
				insertNode(root, key);
				break;
				
			case 4: printf("input what you found: ");
				scanf(" %c", &key);
				foundedNode = searchBST(root, key);
				if (foundedNode != NULL)
					printf("\n found %c \n", foundedNode->key);
				else printf("\n not found \n");
				break;
			
			case 5: return 0;
			
			default: printf("Error, rechoice");
				break;
		}
	}
}
