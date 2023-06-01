//https://www.acmicpc.net/problem/1018

#include <stdio.h>

int main(){
    char arr[50][51];
    int a, b, count = 3000; //count는 초기에 아주 큰 값으로 초기화
    
    printf("문제에 포함된 입력값을 복사\n");
    scanf("%d %d", &a, &b);
    
    for (int i = 0; i < a; i++)
        scanf(" %s", arr[i]);

    int temp1 = 0, temp2 = 0;   //첫째 칸을 W로 할 때, B로 할 때 따로 계산하기 위함
    
    for (int x = 0; x < a - 7; x++) {   //x좌표와
        for (int y = 0; y < b - 7; y++) {   //y좌표가 도착점에 갈 때까지 반복
            //첫째 칸을 W로 만드는 경우
            for (int i = x; i < x + 8; i++) {
                for (int j = y; j < y + 8; j++) {
                    //합이 짝수일 때
                    if (((i - x + j - y) % 2) == 0) {
                        //해당하는 좌표가 W가 아니면
                        if (arr[i][j] != 'W')
                            temp1++;    //다시 칠하기
                    }
                    //합이 홀수일 때
                    else {
                        //해당하는 좌표가 B가 아니면
                        if (arr[i][j] != 'B')
                            temp1++;    //다시 칠하기
                    }
                }
            }
            //첫째 칸을 B로 만드는 경우
            for (int i = x; i < x + 8; i++) {
                for (int j = y; j < y + 8; j++) {
                    if (((i - x + j - y) % 2) == 0) {
                        if (arr[i][j] != 'B')
                            temp2++;
                    }

                    else {
                        if (arr[i][j] != 'W')
                            temp2++;
                    }
                }
            }
            //더 적게 칠한 횟수를 선택하고
            int res = temp1 < temp2 ? temp1 : temp2;
            if (res < count) count = res;   //결과에 저장
            temp1 = 0;
            temp2 = 0;
        }
    }
    printf("%d", count);

    return 0;
}
