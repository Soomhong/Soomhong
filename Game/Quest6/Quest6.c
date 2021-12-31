#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void game(){
	srand(time(NULL));
	printf("Baseball game clc\n");
}

int find(int com[3], int index){
	int re;
	int i;
	
	re = 0;
	for(i=0; i<index; i++){
		if(com[i] == com [index]){
			return 1;
		}
	}
	return re;
}

void comdata(int com[3]){
	int i;
	
	for(i=0; i<3; i++){
		com[i] = rand()%10;
		if(i==find(com,i)){
			i--;
		}
	}
	
}

void playerdata(int p[3]){
	int i;
	
	printf("중복 없이 0~9 숫자 3개 입력: ");
	for(i=0; i<3; i++){
		scanf("%d", &p[i]);
	}
}

void score(int com[3], int p[3], int *s, int *b){
	int i; 
	int j;
	int ts;
	int tb;
	
	
	ts = 0;
	tb = 0;
	
	for(i=0; i<3; i++){
		for(j=0; j<3; i++){
			if(p[i] == com[j]){
				if(i==j){
					ts++;
				}
				else{
					tb++;
				}
				break;
			}
		}
	}
	
	*s = ts;
	*b = tb;
	
}

int nextgame(){
	
	int go;
	int re;
	
	re = 0;
	printf("-1: end else continue game ?");
	scanf("%d", &go);
	if(-1 == go){
		re = -1;
	}
	
	return re;
}

	

int main() {
	int com[3];
	int p[3];
	int s;
	int b;
	
	int i;
	
	game();
	
	while(1){
		
		comdata(com);
		for(i=0; i<10; i++){
			
			b=0;
			s=0;
			
			playerdata(p);
			score(com, p,&s, &b);
		if(3 == s){
			break;
		}
		else{
			printf(" s: %d	b : %d \n", s, b);
			}
		}
	
	
	if (3 ==s){
		printf("3 STRIKE !! YOU WIN...\n");
	}
	else{
		printf("YOU LOSE...\n");
		printf("com => %d %d %d \n",com[0], com[1], com[2]);
	}
	
	if(-1 == nextgame()){
		printf("Thank you! \n");
		break;
	}
}
	return 0;
}
