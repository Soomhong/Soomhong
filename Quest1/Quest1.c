#include <stdio.h>
#include <stdlib.h>


int main() {
	
	int a[10];
	int kor[10];
	int eng[10];
	int math[10];
	int total[10];
	float avg[10];
	int i;
	int j;
	int max = 0;
	
	for(i=0; i<10; i++){
		a[i] = rand()%11;
		kor[i] = rand()%101;
		eng[i] = rand()%101;
		math[i] = rand()%101;
	}
	for(j=0; j<10; j++){
		total[j] = kor[j]+eng[j]+math[j];
		avg[j] = (float)total[j]/3.0;
	
	}
	for(i=0; i<10;i++){
		if(total[max] < total[i]){
			max = i;
		}
	}
	for(j=0; j<10; j++){
		printf("%d] %d	%d	%d	%d	%.2f\n", j, kor[j], eng[j], math[j], total[j], avg[j]);
		
	}
	printf("max index : %d", max);
	return 0;
}
