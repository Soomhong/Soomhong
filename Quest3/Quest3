#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int i;
	int j;
	int data[6];
	
	srand(time(NULL));
	
	for(i=0; i<6; i++){
		data[i]=rand()%46;
		for(j=0; j<i;j++){
			if(data[i]==data[j]){
				i--;
				break;
			}
		}
	}
	
	for(i=0; i<6;i++){
		printf("%d	", data[i]);
	}
	printf("\n");
	
	return 0;
}
