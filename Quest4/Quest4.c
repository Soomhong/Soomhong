#include<stdio.h>
#include<stdlib.h>
/*
//계산기 
void calc(int *a, int *b, int *c, int *d, int *e, float *f){
	
	*c = *a + *b;
	*d = *a - *b;
	*e = *a * *b;
	*f = *a - *b;
}

void print(int *a, int *b, int *c, int *d, int *e, float *f){
	printf("%d + %d = %d\n", *a, *b, *c);
	printf("%d - %d = %d\n", *a, *b, *d);
	printf("%d * %d = %d\n", *a, *b, *e);
	printf("%d / %d = %.1lf\n", *a, *b, *f);

}

int main(){
	int a, b, c, d, e;
	float f;

	printf("input 2 nums: ");
	scanf("%d %d", &a, &b);
	
	calc(&a, &b, &c, &d, &e, &f);
	
	print(&a, &b, &c, &d, &e, &f);

	return 0;
}
*/
/*
//성적 처리 
#include<time.h>
#define SIZE 10

void score(int kor[], int eng[], int math[]){
	
	srand(time(NULL));
	
	for(int i = 0; i < SIZE; i++){
		kor[i] = rand()%101;
		eng[i] = rand()%101;
		math[i] = rand()%101;
	}
}

void sum_avg_calc(int kor[], int eng[], int math[], int sum[], float avg[]){
	for(int i = 0; i < SIZE; i++){
		sum[i] = kor[i] + math[i] + eng [i];
		avg[i] = sum[i] / 3.0;
	}
}

void print(int kor[], int eng[], int math[], int sum[], float avg[]){
	printf("Num\tKor\tEng\tMath\tTotal\tAvg\n");
	for(int i = 0; i < SIZE; i++){
		printf("%d]\t%d\t%d\t%d\t%d\t%.2lf\n", i+1, kor[i], eng[i], math[i], sum[i], avg[i]);
	}
}
int main(){
	int i;
	int sum[SIZE];
	float avg[SIZE];
	int kor[SIZE];
	int eng[SIZE];
	int math[SIZE];
	
	score(kor, eng, math);
	sum_avg_calc(kor,  eng, math, sum, avg);
	print(kor,  eng, math,  sum, avg);
	
	return 0;
}*/
//로또 
#include<time.h>
#define SIZE 6
 
void number(int data[], int size){
	srand(time(NULL));
	for(int i = 0; i < size; i++){
		data[i] = rand()%46;
		for(int j = 0; j < i; j++){
			if(data[i] == data[j]){
				i--;
				break;
			}
		}
	}
}

void print(int data[], int size){
	for(int i = 0; i < size; i++){
		printf("%d\t\t", data[i]);
	}
	printf("\n");
}

int main() {
	
	int data[] = {0};
	
	number(data, 6);
	print(data, 6);
	
	return 0;
}
 
