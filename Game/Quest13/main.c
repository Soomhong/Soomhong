#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mtg.h"

#define F4				64
#define LEFT			75
#define RIGHT			77
#define GUN				32

#define ENEMY			 4
#define ENEMY_TYPE		 4

#define MAX_BULLET		50
#define MAX_BOMB		50

#define PLAYER_YPOS		24



struct OBJECT
{
	int x;
	int y;
	int life;
	int type;
	int dir;
};

int g_game = 0;
struct OBJECT g_enemy[ENEMY];
struct OBJECT g_player;

struct OBJECT g_bullet[MAX_BULLET];
struct OBJECT g_bomb[MAX_BOMB];

char* g_enemy_type[] = {"@@@@", "####", "%%%%", "&&&&"};

void showout();
void showplayer();
void showenemy();
void showbullet();
void shot();
void downbomb(int x, int y);

void showout() {
	_DrawText(60, 20, "F4 : exit");
}

void showplayer() {
	char temp[80];

	_DrawText(g_player.x, g_player.y, "■■■■");
	sprintf(temp, "Life : %d", g_player.life);
	_DrawText(0, 0, temp);
}

void showenemy() {
	int i;
	for (i = 0; i < ENEMY; i++) {
		if (g_enemy[i].life <= 0) continue;

		_DrawText(g_enemy[i].x, g_enemy[i].y, g_enemy_type[g_enemy[i].type]);
	}
}



void showbomb() {
	int i;
	for (i = 0; i < MAX_BOMB; i++) {
		if (g_bomb[i].life <= 0) continue;

		_DrawText(g_bomb[i].x, g_bomb[i].y, "o");
	}
}

void Bomb() {
	int i;
	
	for (i = 0; i < MAX_BOMB; i++) {
		g_bomb[i].life = 0;
		g_bomb[i].dir = 1;
	}
}
void player() {
	g_player.x = 40;
	g_player.y = 60;
	g_player.life = 10;
}
void enemy() {
	int i;

	for (i = 0; i < ENEMY; i++) {
		g_enemy[i].x = rand() % 70;
		g_enemy[i].y = rand() % 5;
		g_enemy[i].life = 10;
		g_enemy[i].type = rand() % ENEMY_TYPE;
		g_enemy[i].dir = 1;
	}
}
void move(char k) { // 좌우방향 움직임 밖에 안됨 갤러그니까..
	switch (k) {
	
	case LEFT :
		g_player.x = g_player.x - 1;

		if (g_player.x < 0) {
			g_player.x = 0;
		}
		break;

	case RIGHT :
		g_player.x = g_player.x + 1;

		if (70 < g_player.x){
			g_player.x = 70;
		}
		break;
	default :
		break;
	}
}

void moveEnemy() {
	int i;

	for (i = 0; i < ENEMY; i++) {
		if (g_enemy[i].life <= 0) continue;
		g_enemy[i].y = g_enemy[i].y + g_enemy[i].dir;

		if (15 <= g_enemy[i].y) {
			g_enemy[i].dir = g_enemy[i].dir * -1;
		}
		else if (g_enemy[i].y <= 0) {
			g_enemy[i].dir = g_enemy[i].dir * -1;
		}
		if (g_enemy[i].dir < 0 && g_enemy[i].y <= 15 && g_enemy[i].y) {
			downbomb(g_enemy[i].x + 2, g_enemy[i].y);
		}
	}
}

void movebomb() {
	int i;

	for (i = 0; i < MAX_BOMB; i++) {
		if (g_bomb[i].life <= 0) continue;

		g_bomb[i].y++;

		if (g_player.y < g_bomb[i].y) {
			g_bomb[i].life = 0;
		}

	}
}

void bombtimer() {
	static long old_bombT = 0;
	long new_bombT;

	new_bombT = _GetTickCount();
	if (abs(new_bombT - old_bombT) < 100) {
		return;
	}
	else {
		old_bombT = new_bombT;
	}

	movebomb();
	Bomb();
	_Invalidate();
}
void enemytimer() {
	static long old_enemyT = 0;
	long new_enemyT;

	new_enemyT = _GetTickCount();
	if (abs(new_enemyT - old_enemyT) < 1000) {
		return;
	}
	else {
		old_enemyT = new_enemyT;
	}

	moveEnemy();

	_Invalidate();
}

void showbullet() {
	int i;

	for (i = 0; i < MAX_BULLET; i++) {
		if (g_bullet[i].life <= 0) continue;

		_DrawText(g_bullet[i].x, g_bullet[i].y, "x");
	}
}

void setbullet() {
	int i;
	for (i = 0; i < MAX_BULLET; i++) {
		g_bullet[i].life = 0;
	}
}

void fire(char k) {
	int i;

	if (GUN == k) {
		for (i = 0; i < MAX_BULLET; i++) {
			if (0 < g_bullet[i].life) continue;

			g_bullet[i].x = g_player.x + 2;
			g_bullet[i].y = g_player.y - 1;
			g_bullet[i].life = 10;
			break;
		}
	}
}

void movebullet() {
	int i;

	for (i = 0; i < MAX_BULLET; i++) {
		if (g_bullet[i].life <= 0) continue;
		g_bullet[i].life = g_bullet[i].life - 1;
		g_bullet[i].y = g_bullet[i].y - 1;
	}
}

void bulletTimer() {
	static long old_bulletT = 0;
	long new_bulletT;

	new_bulletT = _GetTickCount();
	if (abs(new_bulletT - old_bulletT) < 50) {
		return;
	}
	else {
		old_bulletT = new_bulletT;
	}
	movebullet();
	shot();
	_Invalidate();
}

void shot() {
	int i, j;

	for (i = 0; i < MAX_BULLET; i++) {
		if (g_bullet[i].life <= 0) continue;

		for (j = 0; j < ENEMY; j++) {
			if (g_enemy[j].life <= 0) continue;

			if (g_enemy[j].y == g_bullet[j].y) {
				if (g_enemy[j].x <= g_bullet[i].x && g_bullet[i].x <= g_enemy[j].x + 4) {
					g_bullet[i].life = 0;
					g_enemy[j].life--;
					break;
				}
			}
		}
	}
}

void downbomb(int x, int y) {
	int i;
	for (i = 0; i < MAX_BOMB; i++) {
		if (g_bomb[i].life <= 0) {
			g_bomb[i].life = 1;
			g_bomb[i].x = x;
			g_bomb[i].y = y;
			break;
		}
	}
}

int gameover() {
	if (g_player.life <= 0) {
		_Invalidate();
		_MessageBox(0, 0, 20, 10, "PUSSY!");
		return -1;
	}

	return 0;
}

void bomb_shot() {
	int i;

	for (i = 0; i < MAX_BOMB; i++) {
		if (g_bomb[i].life <= 0) continue;

		if (g_bomb[i].y == g_player.y &&
			g_player.x <= g_bomb[i].x && g_bomb[i].x <= g_player.x + 2) {

			g_player.life--;
			g_bomb[i].life = 0;
		}
	}
}
void Draw()
{
	showout();
	showplayer();
	showenemy();
	showbullet();
}

void RunIni()
{
	srand(time(NULL));
	player();
	enemy();
	setbullet();
	Bomb();

	_Invalidate();
}

int RunKey()
{
	char k;

	k=_GetKey();	
	if(-1==k) return 0;
	if ('q' == k || F4 == k);
	{
		return -1;
	}	

	move(k);
	fire(k);
	_Invalidate();

	return 0;
}
void GameMain()
{
	RunIni();
	while(1)
	{
		enemytimer();
		bulletTimer();
		bombtimer();

		if(-1==RunKey())
		{
			break;
			
			
		}
		if (-1 == gameover()) {
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
