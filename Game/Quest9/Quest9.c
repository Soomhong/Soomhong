#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mtg.h"

#define MY_SIZE		4 // 임의로 변경가능, 숫자는 추가해야 함. 
#define MY_BLANK	MY_SIZE*MY_SIZE // 사이즈 변환 시 *표의 위치를 수정하지 않아도 됨.. 
#define MY_LEFT		75 //왼쪽 방향키의 키값 
#define MY_RIGHT	77//오른쪽 방향키의 키값 
#define MY_UP		72//위 방향키의 키값 
#define MY_DOWN		80//아래 방향키의 키값 

int g_data[MY_SIZE][MY_SIZE]={{1,2,3,4},{4,5,6,7},{8,9,10,11},{12,13,14,16}}; //  4 * 4 데이터 박스 설정 
int g_x=MY_SIZE-1;
int g_y=MY_SIZE-1;

void Draw()
{
	int x,y;
	char temp[10];
	
	for(y=0; y<MY_SIZE; y++)
	{
		for(x=0; x<MY_SIZE; x++) 
		{
			sprintf(temp, "%d", g_data[y][x]);
			if(MY_BLANK==g_data[y][x]) // 설정한 데이터 박스의 마지막 숫자(순서대로 입력 시)에 *표 입력 
			{
				sprintf(temp,"*");
			}
			_DrawText(x*3,y*3,temp); // 숫자간 공백 *a a의 숫자가 커질수록 공백이 커짐 
		}
	}
	
	_DrawText(23,2,"22/01/04"); // 숫자 퍼즐 옆 문구 띄우기 
}
void RunIni()
{
	int mix;
	int i;
	
	srand(time(NULL));
	for(i=0; i<100; i++) 
	{
		mix=rand()%4;	// mix 변수를 설정하구 난수를 이용해 무작위로 숫자를 선택해 방향키를 결정하고 for문을 이용해 난수로 정해진 방향으로 100회 섞음 
		switch(mix)
		{
			case 0:
				if(0==Move(g_x-1,g_y,g_x,g_y))
				{
					g_x--;
				}
				break;
			case 1:
				if(0==Move(g_x+1,g_y,g_x,g_y))
				{
					g_x++;
				}
				break;
			case 2:
				if(0==Move(g_x,g_y-1,g_x,g_y))
				{
					g_y--;
				}
				break;
			case 3:
				if(0==Move(g_x,g_y+1,g_x,g_y))
				{
					g_y++;
				}
				break;
			default:
				break;
				
		}
	} 
	
	_Invalidate();
}
int Move(int sx, int sy, int dx, int dy) // 밖으로 나가지 않게 하는 방향키 설정 
{
	if(sx < 0 || sy < 0 || dx < 0 || dy < 0) 
	{
		return -1;
	}
	
	if(MY_SIZE <= sx || MY_SIZE <= sy || MY_SIZE <= dx || MY_SIZE <= dy)
	{
		return -1;
	}
	
	if(MY_BLANK == g_data[dy][dx])
	{
		g_data[dy][dx]=g_data[sy][sx];
		g_data[sy][sx]=MY_BLANK;
		return 0;
	}
	
	return -1;
} 
int CheckGameOver() // 게임 종료 함수 
{
	int x,y;
	int a;
	
	a = 1; //초기화 
	for(y=0;y<MY_SIZE;y++)
	{
		for(x=0;x<MY_SIZE;x++)
		{
			if(a != g_data[y][x]) // 숫자가 제자리에 있는지 검사하는 과정... 
			{
				return -1;
			}
			a++;
		}
	}
	return 0;
} 

int RunKey()	
{
	char k;
	
	k=_GetKey();
	
	if(-1==k) return 0;
	if('q'==k)
	{
		return -1;
	}
	else if(MY_LEFT == k)
	{
		if(0 == Move(g_x-1,g_y,g_x,g_y))
		{
			g_x--;
		}
	}
	else if(MY_RIGHT == k)
	{
		if(0 == Move(g_x+1,g_y,g_x,g_y))
		{
			g_x++;
		}
	}
	else if(MY_UP == k)
	{
		if(0 == Move(g_x,g_y-1,g_x,g_y))
		{
			g_y--;
		}
	}
	else if(MY_DOWN == k)
	{
		if(0 == Move(g_x,g_y+1,g_x,g_y))
		{
			g_y++;
		}
	}

	
	if(0 == CheckGameOver()) 
	{
		_Invalidate();
		_MessageBox(10,10,30,5,"Game Over"); 
	}
	
	_Invalidate();
	
	return 0;
}
void GameMain()
{
	RunIni();
	while(1)
	{
		if(-1==RunKey())
		{
			break;
		}
	}
}

int main() 
{
	_BeginWindow();
	GameMain();
	_EndWindow();
	
	return 0;
}
