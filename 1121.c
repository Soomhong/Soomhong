#include <stdio.h>
#include <stdlib.h>
/*
void inputdata(int *a, int *b)
{
	printf("input 2 data:");
	scanf("%d %d", a, b);
}

void calc(int a, int b, int *c, int *d, int *e, int *f)
{
	*c = a + b;
	*d = a - b;
	*e = a * b;
	*f = a / b;
}

void print(int a, int b, int *c, int *d, int *e, int *f)
{
	printf("%d + %d = %d\n", a, b, *c);
	printf("%d - %d = %d\n", a, b, *d);
	printf("%d * %d = %d\n", a, b, *e);
	printf("%d / %d = %d\n", a, b, *f);
}
int main() {
	
	int a, b, c, d, e, f;
	
	inputdata(&a, &b);
	calc(a, b, &c, &d, &e, &f);
	print(a, b, &c, &d, &e, &f);
	
	return 0;
}
*/
/*
#include <time.h>
#define size 10

void scores(int kor[size], int eng[size], int math[size]){
	int i;
	srand(time(NULL));
	for(i = 0; i<10; i++)
	{
		kor[i] = rand()%101;
		eng[i] = rand()%101;
		math[i] = rand()%101;
	}
}
void calc(int kor[size], int eng[size], int math[size], int sum[size],float avg[size])
{
	int i;
	for(i=0; i<10; i++)
	{
		sum[i] = kor[i]+eng[i]+math[i];
	}
	for(i=0; i<10; i++)
	{
		avg[i] = (float)sum[i] / 3.0;
	}
}
void makemaxindex(int sum[size], int *maxindex)
{
	int i;
	
	*maxindex = 0;
	for(i=0; i<10; i++)
	{
		if(sum[*maxindex] < sum[i])
		{
			*maxindex = i;
		}
	}
}
void print(int kor[size], int eng[size], int math[size], int sum[size], float avg[size], int maxindex)
{
	int i;
	for(i=0; i<10; i++)
	{
	printf("%d] %d	%d	%d	%d	%.2f\n", i, kor[i], eng[i], math[i], sum[i], avg[i]);
	}
	printf("Max index is %d", maxindex);
}
int main()
{
	int maxindex;
	
	int kor[size];
	int eng[size];
	int math[size];
	int sum[size];
	float avg[size];
	
	scores(kor, eng, math);
	calc(kor, eng, math, sum, avg);
	makemaxindex(sum, &maxindex);
	print(kor, eng, math, sum, avg, maxindex);
	
	return 0;
}
*/
/*
#include <time.h>
#define MY_END -1
#define MY_GA 0
#define MY_BA 1
#define MY_BO 2

#define MY_WIN 0
#define MY_LOSE 1

void MyIni(int * count, int *wcount)
{
	*count = 0;
	*wcount = 0;
	srand(time(NULL));
}
int Complay()
{
	return rand()%3;
}
int Manplay()
{
	int you;
	
	printf("-1(end), 0(rock), 1(siccor), 2(paper)?");
	scanf("%d", &you);
	
	return you;
}
int MyCheck(int com, int you)
{
	if(MY_GA==you && MY_BO==com)
	{
		return MY_WIN;
	}
	if(MY_BA==you && MY_GA==com)
	{
		return MY_WIN;
	}
	if(MY_BO==you && MY_BA==com)
	{
		return MY_WIN;
	}	
	
	return MY_LOSE;
}
int main()
{
	int you;
	int com;
	int re;
	int count;
	int wcount;
	float wrate;
	
	MyIni(&count, &wcount);
	
	while(1)
	{
		com=Complay();
		you=Manplay();
		
		if(MY_END==you)
		{
			break;
		}
	
	count++;
	re=MyCheck(com,you);
	if(MY_WIN == re)
	{
		wcount++;
		printf("You win! c:%d, y:%d\n", com , you);
	}
	else
	{
		printf("You lose.. c:%d, y:%d\n", com, you);
	}
}
	return 0;
}
*/
