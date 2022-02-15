#include <stdio.h>
#include <windows.h>
#include <conio.h>


#define Up		72
#define Down		80
#define Left		75
#define Right		77
#define Space		32



void gotoxy(int x,int y) {
    COORD pos={2*x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}


void Drawtitle();

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
int MoveMenu(){
	char key;
	
	int y = 17;
	while(1){
		if(_kbhit()){
			key = _getch();
			
			if(key == -32) {
				key = _getch();
				
				switch (key){
					case Up:
						if(y > 17){
							gotoxy(11, y);
							printf(" ");
							gotoxy(11, --y);
							printf(">");
						}break;
					
					case Down:
						if(y < 19){
							gotoxy(11, y);
							printf(" ");
							gotoxy(11, ++y);
							printf(">");
						}break;
				}
			}
		}
	}
}
int Drawmenu(){

	gotoxy(11,17);printf("> Start\n");
	gotoxy(12,18);printf("Info.\n");
	gotoxy(12,19);printf(" End \n");
}

void Draw(){
	Drawtitle();
	Drawmenu();
	
}



int main() {

	Draw();
	MoveMenu();
	
	return 0;
}
//기존에 짜던거에 덮는데 자꾸 오류나서 그냥 mtg 안쓰는 걸로 갈아엎음
//타이틀, 메뉴 커서 이동까지함 (220215 1307)
