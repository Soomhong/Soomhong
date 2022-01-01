#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mtg.h"

int g_k=-1;

void Draw()
{
	char temp[80];
	
	sprintf(temp,"key:%d",g_k);
	_DrawText(10,10,temp);
}
void RunIni()
{
	_Invalidate();
}
void RunGame()
{
	char k;
	
	RunIni();
	while(1)
	{
		k=_GetKey();
		if(-1==k)
			continue;
		
		if('q'==k)
			break;
		g_k=k;
		_Invalidate();
	}
}

int main() 
{
	_BeginWindow();
	RunGame();
	_EndWindow();
	
	return 0;
}
