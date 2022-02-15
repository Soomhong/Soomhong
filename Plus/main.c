#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define Map_H	22
#define Map_W	12



#define Wall	0
#define Blank	1
#define Block	2
#define SUBMIT	3

#define Up			0
#define Down		1
#define Left		2
#define Right		3
#define Submit		4 //submit

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
	printf("        ↑    Change    \n");
	printf("      ←  →  Move      \n");
	printf("        ↓    Softdrop  \n");
	printf("      Space   Harddrop  \n");
	
	while(1){
		if(keycontrol() == Submit){
			system("cls");
			main();
			break;
		}
	}
}




int main() {
	
	while(1){
		Drawtitle();
		
		int choice = Drawmenu();
		if(choice == 0){
			choose();
		}
		else if(choice == 1){
			Drawinfo();
		}
		
		else if(choice == 2){
			return 0;
		}
		system("cls");
	
	
	return 0;
	}
}
//기존에 짜던거에 덮는데 자꾸 오류나서 그냥 mtg 안쓰는 걸로 갈아엎음
//타이틀, 메뉴 커서 이동까지함 (220215 1307)
//타이틀, 메뉴 커서 이동, 정보 선택, 선택 후 스페이스 바 누르면 타이틀로 돌아오는 기능, 종료 선택 기능 (220215 1729)
