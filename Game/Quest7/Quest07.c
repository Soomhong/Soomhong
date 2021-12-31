#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define word_number 5
#define word_len 10

char Word[word_number][word_len] = { // 설정한 단어 내용 5개 변경 가능 ㅎㅅㅇ
	"cpro"
	,"programing"
	,"hangman"ㅎ 
	,"expand"
	,"quest"
};

int g_step = 0; //전역 변수

void choose_word(char *com, char *player) {
	int a;
	int i;
	int len;
	
	srand(time(NULL)); //난수 설정
	
	a = rand() % word_number; // 무작위로 word 중 한단어 선택

	strcpy(com, Word[a]); //com에 단어 복사

	len = strlen(com); //len에 단어 길이 입력 

	for (i = 0; i < len; i++) { // player의 배열에 *채우기
		player[i] = '*';
	}
	player[i] = '\0';
}

int data(char com[word_len], char player[word_len]) {
	char msg[5];
	char key;

	int len;
	int check;
	int i;


	printf(" Hint: %s \n", player); // 난수로 결정된 단어를 Hint: ****로 표 시 
	printf(" input data: ");
	scanf("%s", msg); //문자열을 입력 받음, 단어를 맞추는 과정 
	key = msg[0];

	len = strlen(player);

	check = 0; //해당하는 단어 입력시 return 값은 0

	for (i = 0; i < len; i++) {
		if (com[i] == key && player[i] == '*') {
			player [i] = key;
			check = 1; // 틀리면 1 반환
		}
	}

	return check;
}

void next() {
	g_step++; // 스위치에 들어갈 수치화된 변수 증가
	printf("Hangman : %d\n", g_step); //행맨 단계 표시
}

void show() { // 행맨 그림 
	switch (g_step) {
	case 0:
			printf("	┌──┐\n");
			printf("          │\n");
			printf("          │\n");
			printf("          │\n");
			printf("          │\n");
		
			break;
		case 1:
			printf("	┌────┐\n");
			printf("	●   │\n");
			printf("             │\n");
			printf("             │\n");
			printf("             │\n");
		
			break;	
		
		case 2:
			printf("	┌────┐\n");
			printf("	●   │\n");
			printf("        ┼    │\n");
			printf("             │\n");
			printf("             │\n");
		
			break;
			
		case 3:
			printf("	┌────┐\n");
			printf("	●   │\n");
			printf("        ┼    │\n");
			printf("        │    │\n");
			printf("             │\n");
		
			break;
		
		case 4:
			printf("	┌────┐\n");
			printf("	●   │\n");
			printf("        ┼    │\n");
			printf("        │    │\n");
			printf("        /┐   │\n");

		break;

		default:
			
		break;
	}
}

int gameover(char* com, char* player) {

	if (4 == g_step) { // 전역 변수가 4가되면 행맨이 다 그려져서 게임이 끝남..
		return 1;
	}
	if (0 == strcmp(com, player)) { // 입력한 단어가 동일하면 단어를 맞춰서 게임이 끝남 ㅎㅅㅎ
		return 1;
	}

	return 0; //둘 다 아니라면 0이 반환
}

int main() {
	char com[word_len];
	char player[word_len];

	choose_word(com, player);

	while (1) {
		if (0 == data(com, player)) { //data 함수에서 0이 반환되면 교수형 단계 진행
			next();
			show();

		}

		if (1 == gameover(com, player)) { //gameover 함수에서 1이 반환되면 함수의 조건 내에서 게임 종료
			break;
		}
	}

	return 0;
}

