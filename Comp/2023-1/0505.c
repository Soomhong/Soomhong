#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;		// 스택 원소의 자료형을 int로 

typedef struct stacknode{	// 스택의 노드를 구조체로 
	element data;
	struct stacknode *link;
}stacknode;


stacknode* top;				//포인터 top 선언 

//스택이 비었는지 확인 
int isEmpty(){
	
	if (top == NULL) return 1;
	else return 0;
}

//
void push(element item){
	
	stacknode* temp = (stacknode *)malloc(sizeof(stacknode));
	temp -> data = item;
	temp -> link = top;
	top = temp;
}

element pop(){
	element item;
	stacknode* temp = top;
	
	if(top == NULL){
		printf("\n\n stack is empty\n");
		return 0;
	}
	
	else{
		item = temp -> data;
		top = temp -> link;
		free(temp);
		return item;
	}
} 

element peek(){
	if(top == NULL){
		printf("\n\n stack is empty\n");
		return 0;
	}
	else return(top -> data);
}

void printStack(){
	stacknode* p = top;
	printf("\n Stack[");
	while (p){
		printf("%d", p -> data);
		p = p -> link;
	}
	printf("]");
}

void main(){
	element item;
	top = NULL;
	printf("\n\n 스택 연결 연산");
	printStack();
	push(1); printStack();
	push(2); printStack();
	push(3); printStack();
	
	item = peek(); printStack();
	printf("\t peek => %d", item);
	
	item = pop(); printStack();
	printf("\t pop  => %d", item);
	
	item = pop(); printStack();
	printf("\t pop  => %d", item);
	
	item = pop(); printStack();
	printf("\t pop  => %d", item);
	
	getchar();
}
