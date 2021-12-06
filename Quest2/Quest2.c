#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 10


int main(){
	
	int i;
	int sum[SIZE];
	double avg[SIZE];
	int kor[SIZE];
	int eng[SIZE];
	int math[SIZE];

	
	
	srand(time(NULL));
	for(i=0; i<SIZE; i++){
	kor[i] = rand()%101;
	eng[i] = rand()%101;
	math[i] = rand()%101;
	}
	
	for(i=0; i<SIZE; i++){
		sum[i] = kor[i] + eng[i] + math[i];
		avg[i] = sum[i] / 3.0;
	}
	printf("Num\tKor\tEng\tMath\tTotal\tAvg\n");
	for(i=0; i<SIZE; i++){
		printf("%d]\t%d\t%d\t%d\t%d\t%.2lf\n", i+1, kor[i], eng[i], math[i], sum[i], avg[i]);
	}
	return 0;
}

