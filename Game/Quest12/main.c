#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mtg.h"

#define F4			 62
#define Enter		 13
#define BackSpace	 8

#define X			 50
#define Y			 20
#define WORD	 	 100
#define LENGTH		 15

int LoadWords();
int GetNextWord();

void ShowHelp();
void ShowScore();
void ShowInput();
void ShowWord();

void RunTimer();
int CheckGameOver();


typedef struct {
	char word[LENGTH];
	int x;
	int y;
	int index;

}	S_WORD;

int g_word_size = 0;
char g_words[WORD][LENGTH];

S_WORD g_word;
S_WORD g_user;

int g_play = 0;
int g_score = 0;

int LoadWords() {
	int index;
	char temp[80];
	FILE* fp;
	char* token;

	fp = fopen("words.jpg", "r");
	if (NULL == fp);
	return -1;

	index = 0;
	while (1) {
		if (NULL == fgets(temp, sizeof(temp), fp)) {
			break;
		}
		token = strtok(temp, ",\n");
		while (1) {
			strcpy(g_words[index], token);
			index++;

			token = strtok(NULL, ",\n");
			if (NULL == token) {
				break;
			}

		}
	}
	g_word_size = index;
	fclose(fp);

	return 0;
}

int GetNextWord() {
	if (g_word_size <= g_word.index) {
		return -1;
	}
	else {
		g_word.x = rand()%X;
		g_word.y = 1;
	}
	strcpy(g_word.word, g_words[g_word.index]);
	g_word.index++;
}

void ShowScore() {

	char temp[20];

	sprintf(temp, "score: %d", g_score);
	_DrawText(0, 0, temp);
}
void ShowHelp() {

	_DrawText(X + 10, 10, "Quest 12 ver.1");
	_DrawText(X + 10, 10, "F4 to exit");
}

void ShowWord() {

	_DrawText(g_word.x, g_word.y,g_word.word);
}

void ShowInput() {

	_DrawText(g_user.x, g_user.y, g_user.word);

}

void Draw() {

		ShowHelp();
		ShowScore();
		ShowInput();
		ShowWord();
}

void RunTimer() {
	static long oldT = 0;
	long newT;

	if (-1 == g_play) return;

	newT = _GetTickCount();
	if (abs(newT - oldT) < 1000) {
		return;
	}
	else {
		oldT = newT;
	}

	if (Y < (g_word.y + 1)) {
		if (-1 == GetNextWord())
		{
			g_play = -1;
		}
	}
	else {
		g_word.y++;
	}

	_Invalidate();
}
int CheckGameOver() {
	if (-1 == g_play) {
		_Invalidate();
		_MessageBox(0, 0, 20, 5, "Game Over");
		return -1;
	}

	return 0;
}

void RunIni()
{
	if (-1 == LoadWords()) {

		_MessageBox(0, 0, 30, 20, "File Load error");
	}

	g_word.index = 0;
	GetNextWord();

	g_user.index = 0;
	g_user.x = 10;
	g_user.y = Y + 1;
	g_user.word[0] = '\0';

	_Invalidate();
}

int RunKey()
{
	char k;

	k = _GetKey();

	if (-1 == k) return 0;
	if ('q' == k || F4 == k)
	{
		return -1;
	}
	else
	{

	}

	if (Enter == k)
	{
		if (0 == strcmp(g_user.word, g_word.word))
		{
			g_score = g_score + 100;
			if (-1 == GetNextWord())
			{
				g_play = -1;
				return 0;
			}
		}

		g_user.index = 0;
		g_user.word[g_user.index] = '\0';
	}
	else if (BackSpace == k) {
		g_user.index--;
		if (g_user.index < 0) {
			g_user.index = 0;
		}
		g_user.word[g_user.index] = '\0';
	}
	else {
		g_user.word[g_user.index++] = k;
		g_user.word[g_user.index] = '\0';
	}

	_Invalidate();

	return 0;

}

void GameMain()
{
	RunIni();
	while (1) {
		RunTimer();
		if(-1==CheckGameOver())	{
			break;
		}
		if(-1==RunKey()) {
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
