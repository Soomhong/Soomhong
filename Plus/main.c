#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define Map_H	22
#define Map_W	12



#define Wall		0
#define Blank		1
#define A_Block		2
#define IA_Block	4

#define Up			0
#define Down		1
#define Left		2
#define Right		3
#define Submit		4 //submit

typedef struct {
	int x;
	int y;
}S_POINT;

int g_data[Map_H][Map_W];

void gotoxy(int x,int y) {
    COORD pos={2*x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

int keycontrol(){
	int temp = _getch();
	
	if(temp == 72){
		return Up;
	}
	
	else if(temp == 80){
		return Down;
	}
	
	else if(temp == 75){
		return Left;
	}
	
	else if(temp == 77){
		return Right;
	}
	
	else if(temp == 32){
		return Submit;
	}
}
#define N_BLOCK 7
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
		{1,1,1,0,0,1,2,1},//ㅗ 
		{1,1,0,1,1,2,1,0},//ㅓ
		{1,1,0,1,2,1,1,2},//ㅜ
		{1,1,1,2,2,1,1,0},//ㅏ
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
	{//왼 갈고리
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

void Drawtitle(){
	int x = 5;
	int y = 4;
	
	gotoxy(x,y+0);printf("\n\n");
	gotoxy(x,y+1);printf("□□□□□□□□□□□□□□□□□\n");Sleep(100);
	gotoxy(x,y+2);printf("□                              □\n");Sleep(100);
	gotoxy(x,y+3);printf("□                              □\n");Sleep(100);
	gotoxy(x,y+4);printf("□                              □\n");Sleep(100);
	gotoxy(x,y+5);printf("□                              □\n");Sleep(100);
	gotoxy(x,y+6);printf("□      ★              ★      □\n");Sleep(100);
	gotoxy(x,y+7);printf("□                              □\n");Sleep(100);
	gotoxy(x,y+8);printf("□                              □\n");Sleep(100);
	gotoxy(x,y+9);printf("□                              □\n");Sleep(100);
	gotoxy(x,y+10);printf("□                              □\n");Sleep(100);
	gotoxy(x,y+11);printf("□□□□□□□□□□□□□□□□□\n");Sleep(100);
	gotoxy(x+6,y+6);printf("T E T R I S");Sleep(100);
	
}

int Drawmenu(){
	int x = 11;
	int y = 17;
	
	gotoxy(x,17);printf("> Start\n");
	gotoxy(x+1,18);printf("Info.\n");
	gotoxy(x+1,19);printf(" End \n");
	
	while(1){
		int n = keycontrol();
		switch(n){
			
			case Up:
				if(y>17){
					gotoxy(x, y);
					printf(" ");
					gotoxy(x, --y);
					printf(">");
				}
				break;
				
			case Down:
				if(y < 19){
					gotoxy(x, y);
					printf(" ");
					gotoxy(x, ++y);
					printf(">");
				}
				break;
			
			case Submit:
				return y -17;
			}
		}
	}



void DrawBlock() {

	int x, y, i;

	for (i = 0; i < 4; i++) {
		x = g_pos.x + g_type[g_patindex][g_dir][i].x;
		y = g_pos.y + g_type[g_patindex][g_dir][i].y;
		gotoxy(x, y);
		
		printf("■");
	}
}
	
int choose(){
	int x = 11;
	int y = 17;
	int key;
	
	system("cls");
	printf("\n\n");
	
	gotoxy(x, y);
	printf("> Easy");
	gotoxy(x+1,y+1);
	printf("Hard");
	gotoxy(x+1,y+2);
	printf("Back");
	
	while(1){
		if(_kbhit()){
			int n = keycontrol();
			switch (n){
				case Up:
					if(y > 17){
						gotoxy(x, y);
						printf(" ");
						gotoxy(x, --y);
						printf(">");
					}break;
					
				case Down:
					if(y < 19){
						gotoxy(x, y);
						printf(" ");
						gotoxy(x, ++y);
						printf(">");
					}break;
				
				case Submit:
					return y-17;
				}
			}
		}
	}

void Drawinfo(){
	system("cls");
	printf("\n\n");
	printf("        ↑    	Change    \n\n");
	printf("    ←      →  Move      \n\n");
	printf("        ↓    	Softdrop  \n\n");
	printf("      Space   	Harddrop  \n\n");
	printf("                        Press Space to go back	\n");
	
	while(1){
		if(keycontrol() == Submit){
			system("cls");
			main();
			break;
		}
	}
}

void Drawmap(){
	int x, y;
	int board[Map_H][Map_W];
	
	for (y = 0; y < Map_H; y++) {
		for (x = 0; x < Map_W; x++) {
			if (0 == x || y == 0 || Map_W == (x + 1) || Map_H == (y + 1)) {
				board[y][x] = Wall;
			}
			else {
				board[y][x] = Blank;
			}
		}
	}
	
	for (y = 0; y < Map_H; y++) {
		for (x = 0; x < Map_W; x++) {
			if (Wall == board[y][x]){

				gotoxy(x , y);
				printf("□");
			}
			else if (Blank == board[y][x]) {

				gotoxy(x * 2, y);
				printf(" ");
			}
			else {

				gotoxy(x * 2, y);
				printf("■");
			}
		}
	}
}


int main() {
	srand(time(NULL));
	int i;
	
	g_pos.x = 1 + rand() % (Map_W - 5);	//내려오는 방향 
	g_pos.y = 1;
	
	g_dir = rand() % 4; 	//블럭 패턴
	 
	g_patindex = rand() % N_BLOCK; //블럭 모양
	 
	DrawBlock();
	
	
/*
	while(1){
		Drawtitle();
		
		int choice = Drawmenu();
		if(choice == 0){
			int choice = choose();
			
			if(choice == 0){
				system("cls");
				Drawmap();Sleep(1000);
				//떨어지는 속도 적당히//easy 
			}
			else if(choice == 1){
				system("cls");
				Drawmap();Sleep(1000);
				//떨어지는 속도 올림//hard
			}
			else if(choice == 2){
				system("cls");
				main();
			}
		}
		else if(choice == 1){
			Drawinfo();
		}
		
		else if(choice == 2){
			return 0;
		}
		system("cls");
	
	*/
	return 0;
	}

//기존에 짜던거에 덮는데 자꾸 오류나서 그냥 mtg 안쓰는 걸로 갈아엎음
//타이틀, 메뉴 커서 이동까지함 (220215 1307)
/*타이틀, 메뉴 커서 이동, 정보 선택,
선택 후 스페이스 바 누르면 타이틀로 돌아오는 기능, 종료 선택 기능 (220215 1729)*/
/*Start 버튼 선택 후 Easy, Hard 맵 구성, Back 선택 후 타이틀로 돌아오는 기능,
블럭 패턴추가, 정보창 스페이스바 문구 추가	(220216 1158)*/
/*무작위 블럭 설정..블럭이 쪼그만게 자꾸 나온다..뭐 잘못했다..(220216 1253)*/ 
