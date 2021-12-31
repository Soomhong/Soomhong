#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define dic_size	5
#define word_len	10

char g_dic[dic_size][word_len]={ //사전 내 단어 설정 
	"father"
	,"mother"
	,"dog"
	,"hello"
};

int g_step = 0; // 다음 단계 변수 설 저 

void ingame(char* com, char* p){
	int index;
	int i;
	int len;
	
	srand(time(NULL)); //난 수 
	
	index=rand()%dic_size;// 인덱스는 0~4 중 하나 
	
	strcpy(com, g_dic[index]); // com에 사전의 내용 입 
	
	len=strlen(com); //문자열 길이 확 인 
	
	for(i=0; i<len; i++){ //단어에 *표 표시 
		p[i]='*';
		
	}
	p[i]='\0';
	
	
}
int inputdata(char com[word_len], char p[word_len]){
	char msg[5];
	char key;
	
	int len;
	int check;
	int i;
	
	
	printf(" Hint: %s \n", p); // ex) Hint: ****로 표 시 
	printf(" input data: "); 
	scanf("%s", msg); //문자를 입력 받음 
	key = msg[0];
	
	len = strlen(p);
	
	check = 0;
	
	for(i=0; i<len; i++){
		if(com[i]==key && p[i]=='*'){
			p[i]=key;
			check = 1;
		}
	}
	
	return check;
}

void next(){
	g_step++;
	printf("hang man:%d\n",g_step); //다음 단계로 넘어가는 함수 
}
void showman(){ // 행맨 그림 
	switch(g_step){
		case 0:
			printf("	┌──┐\n");
			printf("		  │\n");
			printf("		  │\n");
			printf("		  │\n");
			printf("		  │\n");
		
			break;
		case 1:
			printf("	┌──┐\n");
			printf("	●	  │\n");
			printf("		  │\n");
			printf("		  │\n");
			printf("		  │\n");
		
			break;	
		
		case 2:
			printf("	┌──┐\n");
			printf("	●	  │\n");
			printf("	┼	  │\n");
			printf("		  │\n");
			printf("		  │\n");
		
			break;
			
		case 3:
			printf("	┌──┐\n");
			printf("	●	  │\n");
			printf("	┼	  │\n");
			printf("	│	  │\n");
			printf("		  │\n");
		
			break;
		
		case 4:
			printf("	┌──┐\n");
			printf("	●	  │\n");
			printf("	┼	  │\n");
			printf("	│	  │\n");
			printf("   ┌┐	  │\n");
		
			break;
		
		default:
			break;
	}
}
int checkgameover(char* com, char* p){ // 게임이 끝내는 경우의 함수 
	if(4==g_step){
		return 1;
	}
	if(0==strcmp(com, p)){
		return 1;
	}
	
	return 0;
}
int main() {
	char com[word_len];
	char p[word_len];
	
	ingame(com, p);
	
	while(1){
		if(0 == inputdata(com,p)){
			next();
			showman(); 
			
		}
		
		if(1==checkgameover(com, p)){
			break; 
		}
	}
	return 0;
}
