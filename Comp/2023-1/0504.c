#include <stdio.h>
struct a{
		char name[51];
		char grade[51];
		double credit;
		double temp;
	};
	
int main(){
	
	struct a list[21];
	
	double sum1;
	double sum2;
	double res;
	
	for(int i = 0; i < 20; i++){
		scanf("%s %lf %s", &list[i].name, &list[i].credit, &list[i].grade);
		if(list[i].grade == 'P'){
			list[i].credit = 0;
		}
		
		else if(list[i].grade == 'A+'){
			list[i].temp = 4.5;
		}
		else if(list[i].grade == 'A0'){
			list[i].temp = 4.0;
		}
		else if(list[i].grade == 'B+'){
			list[i].temp = 3.5;
		}
		else if(list[i].grade == 'B0'){
			list[i].temp = 3.0;
		}
		
		else if(list[i].grade == 'C+'){
			list[i].temp = 2.5;
		}
		
		else if(list[i].grade == 'C0'){
			list[i].temp = 2.0;
		}
		
		else if(list[i].grade == 'D+'){
			list[i].temp = 1.5;
		}
		
		else if(list[i].grade == 'D0'){
			list[i].temp = 1.0;
		}
		
		else if(list[i].grade == 'F'){
			list[i].temp = 0.0;
		}
	}
	
	for(int i = 0; i < 20; i++){
		//printf("\n%s %.1lf %s\n\n", list[i].name, list[i].credit, list[i].grade);
		sum1 += list[i].credit;
		sum2 =  list[i].temp * list[i].credit;
	}
	
	res = sum2 / sum1;
	
	//printf("%.1lf", sum1);
	
	printf("%.1lf", res);
	
	return 0;
}
