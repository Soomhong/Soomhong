#include <stdio.h>
#include <stdlib.h>
#include "mtg.h"

#define Map_W		10 + 2 // 게임 공간 크기
#define Map_H		20 + 2
#define WALL		0 // 벽 확인, 빈공간에 블럭표시, 게임 공간생성.
#define BLANK	1
#define BLOCK	2

#define N_BLOCK		 7 // 블럭 수
#define LEFT		75
#define RIGHT	77
#define UP		72
#define DOWN		80
#define SPACE	32

typedef struct { // 블럭 생성을 위한 구조체
	int x;
	int y;
} S_POINT;

int g_data[Map_H][Map_W]; // 크기 설정
S_POINT g_type[N_BLOCK][4][4] = { 
	{//막대
		{0,0,1,0,2,0,3,0},
		{1,0,1,1,1,2,1,3},
		{0,0,1,0,2,0,3,0},
		{1,0,1,1,1,2,1,3}
	},
	{//네모
		{1,1,2,1,1,2,2,2},
		{1,1,2,1,1,2,2,2},
		{1,1,2,1,1,2,2,2},
		{1,1,2,1,1,2,2,2}
	},
	{//그 모양
		{1,1,0,1,2,1,1,2},
		{1,1,1,2,2,1,1,0},
		{1,1,1,0,0,1,2,1},
		{1,1,0,1,1,2,1,0},
	},
	{//오른 계단
		{0,0,1,0,1,1,2,1},
		{1,1,0,1,0,2,1,0},
		{0,0,1,0,1,1,2,1},
		{1,1,0,1,0,2,1,0},
	},
	{//왼 계단
		{1,1,0,1,1,0,2,0},
		{1,1,1,2,0,1,0,0},
		{1,1,0,1,1,0,2,0},
		{1,1,1,2,0,1,0,0}
	},
	{//왼 갈고리고침!
		{1,1,1,2,1,0,0,2},
		{1,1,0,1,2,1,0,0},
		{1,1,1,0,2,0,1,2},
		{1,1,0,1,2,1,2,2}
	},
	{//오른 갈고리
		{1,1,1,2,2,2,1,0},
		{1,1,2,1,0,1,1,0},
		{1,1,1,0,1,2,0,0},
		{1,1,0,1,0,2,2,1}
	}
	
		
	
}; // 패턴

int g_dir = 0;

int g_patindex = 0;

S_POINT g_pos = {1, 1};

void DataIni();

void DataIni() {
	int x, y;

	for (y = 0; y < Map_H; y++) {
		for (x = 0; x < Map_W; x++) {
			if (0 == x || y == 0 || Map_W == (x + 1) || Map_H == (y + 1)) {
				g_data[y][x] = WALL;
			}
			else {
				g_data[y][x] = BLANK;
			}
		}
	}
}
void DrawData()
{
	int x, y;

	for (y = 0; y < Map_H; y++) {
		for (x = 0; x < Map_W; x++) {
			if (WALL == g_data[y][x]){

				_DrawText(x * 2, y, "□");
			}
			else if (BLANK == g_data[y][x]) {

				_DrawText(x * 2, y, ".");
			}
			else {

				_DrawText(x * 2, y, "■");
			}
		}
	}
}

void DrawBlock() {

	int x, y, i;

	for (i = 0; i < 4; i++) {
		x = g_pos.x + g_type[g_patindex][g_dir][i].x;
		y = g_pos.y + g_type[g_patindex][g_dir][i].y;
		_DrawText(x * 2, y, "■");
	}
}

void DrawHelp() {
	_DrawText(32, 10, "Quest 11");
	_DrawText(32, 11, " PRESS Q : 종료 / ←, → : 이동 / ↑, ↓ : 회전");
}

void Draw()
{
	DrawData();
	DrawBlock();
	DrawHelp();

}

void RunIni()
{
	DataIni();
	_Invalidate();
}

int CheckBlockMove(int dx, int dy, int dir) {
	int x, y;
	int i;

	for (i = 0; i < 4; i++) {
		x = dx + g_type[g_patindex][dir][i].x;
		y = dy + g_type[g_patindex][dir][i].y;
		if (BLANK != g_data[y][x]) {
			return -1;
		}
	}

	return 0;
}

int MoveBlockDown() {
	if (0 == CheckBlockMove(g_pos.x, g_pos.y + 1, g_dir)) {
		g_pos.y++;
		return 0;
	}
	return -1;
}

void CopyBlockToData() {
	int x, y;
	int i;

	for (i = 0; i < 4; i++) {
		x = g_pos.x + g_type[g_patindex][g_dir][i].x;
		y = g_pos.y + g_type[g_patindex][g_dir][i].y;

		g_data[y][x] = BLOCK;
	}
}

void GetNewBlock() {
	g_pos.x = 1 + rand() % (Map_W - 5);
	g_pos.y = 1;
	g_dir = rand() % 4;
	g_patindex = rand() % N_BLOCK;
}

void DownBlock(int y) {
	int x;

	for (; 1 <= y; y--) {
		for (x = 1; x < Map_W - 1; x++) {
			if (1 == y) {
				g_data[y][x] = BLANK;
			}
			else {
				g_data[y][x] = g_data[y - 1][x];
			}
		}
	}
}

void CheckSameBlock() {
	int x, y;

	for (y = Map_H - 2; 0 < y; y--) {
		int same = 0;
		for (x = 1; x < Map_W - 1; x++) {
			if (BLOCK != g_data[y][x]) {
				same = -1;
				break;
			}
		}

		if (0 == same) {
			DownBlock(y);
			y++;
		}
	}
}

void MoveToEnd() {
	while (1) {
		if (-1 == MoveBlockDown()) {
			CopyBlockToData();
			CheckSameBlock();

			GetNewBlock();

			break;
		}
	}
}
void RunTimer() {
	static long oldT = 0;
	long newT;
	static int killTimer = 0;

	if (-1 == killTimer)
		return;

	newT = _GetTickCount();
	if (abs(newT - oldT) < 100) {
		return;
	}
	else {
		oldT = newT;
	}

	if (-1 == MoveBlockDown()) {
		CopyBlockToData();
		CheckSameBlock();

		GetNewBlock();

		if (-1 == MoveBlockDown()) {
			_Invalidate();
			killTimer = -1;
			_MessageBox(40, 10, 20, 10, "Game Over!");
		}
	}

	_Invalidate();
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
	else
	{

	}

	if (LEFT == k) {
		if (0 == CheckBlockMove(g_pos.x - 1, g_pos.y, g_dir)) {
			g_pos.x--;
		}
	}
	else if (RIGHT == k) {
		if (0 == CheckBlockMove(g_pos.x + 1, g_pos.y, g_dir)) {
			g_pos.x++;
		}
	}
	else if (SPACE == k) {
		MoveToEnd();
	}
	else if (UP == k) {
		int dir = g_dir;

		dir++;
		if (3 < dir) dir = 0;
		if (0 == CheckBlockMove(g_pos.x, g_pos.y, dir)) {
			g_dir = dir;

			_Invalidate();
		}
	}
	else if (DOWN == k) {
		int dir = g_dir;

		dir--;
		if (dir < 0) dir = 3;
		if (0 == CheckBlockMove(g_pos.x, g_pos.y, dir)) {
			g_dir = dir;

			_Invalidate();
		}
	}

	_Invalidate();

	return 0;
}
void GameMain()
{
	
	RunIni();
	while(1)
	{
		RunTimer();
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
