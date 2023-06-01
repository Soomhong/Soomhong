#include <stdio.h>
#inlcude <stdlib.h>
#define Q-SIZE 4

typedef char element;
typedef struct{
	element queue[Q_SIZE];
	int front, rear;
} Queuetype;

Queuetype *createQueue(){
	Queuetype *Q;
	Q =  (Queuetype *)malloc(sizeof(Queuetype));
	Q -> front = -1;
	Q -> rear = -1;
	return Q;
}

int isEmpty(Queuetype *Q){
	if(Q->front == Q -> rear){
		printf("Queue is empty");
		return 1;
	}
	else return 0;
}

int isFull(Queuetype *Q){
	if(Q->rear = Q_SIZE -1){
		printf("Queue is full");
		return 1;
	}
	else return 0;
}

void enQueue(Queuetype *Q, element item){
	if(isFull(Q)) return;
	else {
		Q -> front++;
		return Q->front queue[Q->fornt];
	}
}

element peek(Queuetype *Q){
	int i;
	printf("Queue: [");
	for(i = Q->fornt+1; i <= Q->rear; i++)
		printf("%3c", Q -> queue[i]);
	printf("]");
}

void main(){
	Queuetyp *Q1 = create.//
}
