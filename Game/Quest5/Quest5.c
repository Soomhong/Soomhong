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
