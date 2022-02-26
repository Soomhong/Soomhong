#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

#define UP 72
#define DOWN 80
#define LEFT 75 
#define RIGHT 77
#define SPACE 32
#define p 112
#define P 80
#define ESC 27

#define false 0
#define true 1

#define A_BLOCK -2 
#define Ceilling -1    
#define empty 0   
#define Wall 1
#define IA_BLOCK 2

#define Map_w 11
#define Map_h 23
#define Map_w_adj 3
#define Map_h_adj 1 

#define stat_x_adj Map_w_adj+Map_w+1

int stat_y_goal;
int stat_y_level;


void gotoxy(int x, int y) {
    COORD pos = { 2 * x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void setcursortype(CURSOR_TYPE c) {  
    CONSOLE_CURSOR_INFO CurInfo;

    switch (c) {
    case NOCURSOR:
        CurInfo.dwSize = 1;
        CurInfo.bVisible = FALSE;
        break;
    case SOLIDCURSOR:
        CurInfo.dwSize = 100;
        CurInfo.bVisible = TRUE;
        break;
    case NORMALCURSOR:
        CurInfo.dwSize = 20;
        CurInfo.bVisible = TRUE;
        break;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

int blocks[7][4][4][4] = {
{{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},
 {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}},
{{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0}},
{{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0},
 {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0}},
{{0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0},{0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0}},
{{0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0},{0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0},{0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0}}
};

int bx;
int by;

int main_org[Map_h][Map_w];
int main_cpy[Map_h][Map_w];

int b_type; 
int b_rotation; 
int b_type_next; 

int key; 

int speed;
int level; 
int level_goal; 
int cnt;

int new_block_on = 0; 
int crush_on = 0;
int level_up_on = 0;
int space_key_on = 0; 

void title(){
	int x = 5;
	int y = 5;
	int cnt;
	
	gotoxy(x, y + 0); printf("■□□□■■■□□■■□□■■"); Sleep(100);
    gotoxy(x, y + 1); printf("■■■□  ■□□    ■■□□■"); Sleep(100);
    gotoxy(x, y + 2); printf("□□□■              □■  ■"); Sleep(100);
    gotoxy(x, y + 3); printf("■■□■■  □  ■  □□■□□"); Sleep(100);
    gotoxy(x, y + 4); printf("■■  ■□□□■■■□■■□□"); Sleep(100);
    gotoxy(x+5, y + 2); printf("T E T R I S"); Sleep(100);
    gotoxy(x+2, y + 6); printf("Press Enter to Start");
    
    getch(); 
}

void reset_main() { 
    int i, j;

    for (i = 0; i < Map_h; i++) { 
        for (j = 0; j < Map_w; j++) {
            main_org[i][j] = 0;
            main_cpy[i][j] = 100;
        }
    }
    for (j = 1; j < Map_w; j++) { 
        main_org[3][j] = Ceilling;
    }
    for (i = 1; i < Map_h - 1; i++) {
        main_org[i][0] = Wall;
        main_org[i][Map_w - 1] = Wall;
    }
    for (j = 0; j < Map_w; j++) { 
        main_org[Map_h - 1][j] = Wall;
    }
}

void reset_main_cpy() {
    int i, j;

    for (i = 0; i < Map_h; i++) {
        for (j = 0; j < Map_w; j++) {
            main_cpy[i][j] = 100;
        }
    }
}

void draw_map() { 
    int y = 3;   
                         
    gotoxy(stat_x_adj, stat_y_level = y); printf(" LEVEL : %5d", level);
    gotoxy(stat_x_adj, stat_y_goal = y + 1); printf(" GOAL  : %5d", 10 - cnt);
    gotoxy(stat_x_adj, y + 3); printf("+--  N E X T  --+ ");
    gotoxy(stat_x_adj, y + 4); printf("|               | ");
    gotoxy(stat_x_adj, y + 5); printf("|               | ");
    gotoxy(stat_x_adj, y + 6); printf("|               | ");
    gotoxy(stat_x_adj, y + 7); printf("|               | ");
    gotoxy(stat_x_adj, y + 8); printf("+---------------+ ");
	gotoxy(stat_x_adj, y + 10); printf("  △   : Shift        SPACE : Hard Drop");
    gotoxy(stat_x_adj, y + 11); printf("◁  ▷ : Left / Right   P   : Pause");
    gotoxy(stat_x_adj, y + 12); printf("  ▽   : Soft Drop     ESC  : Quit");
}

void draw_main() {
    int i, j;

    for (j = 1; j < Map_w - 1; j++) {
        if (main_org[3][j] == empty) main_org[3][j] = Ceilling;
    }
    for (i = 0; i < Map_h; i++) {
        for (j = 0; j < Map_w; j++) {
            if (main_cpy[i][j] != main_org[i][j]) {                                            
                gotoxy(Map_w_adj + j, Map_h_adj + i);
                switch (main_org[i][j]) {
                case empty:
                    printf("  ");
                    break;
                case Ceilling:
                    printf(". ");
                    break;
                case Wall:
                    printf("▩");
                    break;
                case IA_BLOCK:
                    printf("□");
                    break;
                case A_BLOCK:
                    printf("■");
                    break;
                }
            }
        }
    }
    for (i = 0; i < Map_h; i++) {
        for (j = 0; j < Map_w; j++) {
            main_cpy[i][j] = main_org[i][j];
        }
    }
}

void move_block(int dir) {
    int i, j;

    switch (dir) {
    case LEFT:
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = empty;
            }
        }
        for (i = 0; i < 4; i++) { 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j - 1] = A_BLOCK;
            }
        }
        bx--;
        break;

    case RIGHT:
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = empty;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j + 1] = A_BLOCK;
            }
        }
        bx++;
        break;

    case DOWN:
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = empty;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i + 1][bx + j] = A_BLOCK;
            }
        }
        by++;
        break;

    case UP:
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = empty;
            }
        }
        b_rotation = (b_rotation + 1) % 4;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = A_BLOCK;
            }
        }
        break;

    case 100:
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = empty;
            }
        }
        b_rotation = (b_rotation + 1) % 4;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i - 1][bx + j] = A_BLOCK;
            }
        }
        by--;
        break;
    }
}

void check_line() {
    int i, j, k, l;

    int block_amount;
    int combo = 0; 

    for (i = Map_h - 2; i > 3;) {
        block_amount = 0; 
        for (j = 1; j < Map_w - 1; j++) {
            if (main_org[i][j] > 0) block_amount++;
        }
        if (block_amount == Map_w - 2) {
            if (level_up_on == 0) {         
                cnt++;
                combo++; 
            }
            for (k = i; k > 1; k--) { 
                for (l = 1; l < Map_w - 1; l++) {
                    if (main_org[k - 1][l] != Ceilling) main_org[k][l] = main_org[k - 1][l];
                    if (main_org[k - 1][l] == Ceilling) main_org[k][l] = empty;
                }
            }
        }
        else i--;
    }
    if (combo) {
        if (combo > 1) { 
            gotoxy(Map_w_adj + (Map_w / 2) - 1, Map_h_adj + by - 2); printf("%d COMBO!", combo);
            Sleep(500);
            
            reset_main_cpy();

        }
        gotoxy(stat_x_adj, stat_y_goal); printf(" GOAL  : %5d", (cnt <= 10) ? 10 - cnt : 0);
    }
}

void drop_block(){
	int i, j;
	
		if (crush_on && check_crush(bx, by + 1, b_rotation) == true) crush_on = 0;
    if (crush_on && check_crush(bx, by + 1, b_rotation) == false) {
        for (i = 0; i < Map_h; i++) { 
            for (j = 0; j < Map_w; j++) {
                if (main_org[i][j] == A_BLOCK) main_org[i][j] = IA_BLOCK;
            }
        }
        crush_on = 0; 
        check_line(); 
        new_block_on = 1; 
        return; 
    }
    if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN); 
    if (check_crush(bx, by + 1, b_rotation) == false) crush_on++; 
}

void new_block() { 
    int i, j;

    bx = (Map_w / 2) - 1;
    by = 0;  
    b_type = b_type_next;
    b_type_next = rand() % 7; 
    b_rotation = 0;  
    new_block_on = 0; 

    for (i = 0; i < 4; i++) { 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = A_BLOCK;
        }
    }
    for (i = 1; i < 3; i++) { 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(stat_x_adj + 2 + j, i + 7);
                printf("■");
            }
            else {
                gotoxy(stat_x_adj + 2 + j, i + 7);
                printf("  ");
            }
        }
    }
}

void check_key() {
    key = 0;

    if (kbhit()) { 
        key = getch();
        if (key == 224) {
            do { key = getch(); } while (key == 224);
            switch (key) {
            case LEFT: 
                if (check_crush(bx - 1, by, b_rotation) == true) move_block(LEFT);
                break;             
            case RIGHT:
                if (check_crush(bx + 1, by, b_rotation) == true) move_block(RIGHT);
                break;
            case DOWN:
                if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN);
                break;
            case UP:
                if (check_crush(bx, by, (b_rotation + 1) % 4) == true) move_block(UP);
                
                else if (crush_on == 1 && check_crush(bx, by - 1, (b_rotation + 1) % 4) == true) move_block(100);
            }                    
        }
        else { 
            switch (key) {
            case SPACE:
                space_key_on = 1;
                while (crush_on == 0) {
                    drop_block();                    
                }
                break;
            case P: 
            case p: 
                pause(); 
                break;
            case ESC: 
                system("cls");
                exit(0); 
            }
        }
    }
    while (kbhit()) getch(); 
}

int check_crush(int bx, int by, int b_rotation) { 
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) { 
            if (blocks[b_type][b_rotation][i][j] == 1 && main_org[by + i][bx + j] > 0) return false;
        }
    }
    return true; 
};





void check_level_up() {
    int i, j;

    if (cnt >= 10) { 
        draw_main();
        level_up_on = 1;  
        level += 1; 
        cnt = 0;   

        for (i = 0; i < 4; i++) {
            gotoxy(Map_w_adj + (Map_w / 2) - 3, Map_h_adj + 4);
            printf("             ");
            gotoxy(Map_w_adj + (Map_w / 2) - 2, Map_h_adj + 6);
            printf("             ");
            Sleep(200);

            gotoxy(Map_w_adj + (Map_w / 2) - 3, Map_h_adj + 4);
            printf("LEVEL UP!");
            gotoxy(Map_w_adj + (Map_w / 2) - 2, Map_h_adj + 6);
            printf("SPEED UP!");
            Sleep(200);
        }
        reset_main_cpy(); 


        for (i = Map_h - 2; i > Map_h - 2 - (level - 1); i--) {
            for (j = 1; j < Map_w - 1; j++) {
                main_org[i][j] = IA_BLOCK;  
                
        check_line(); 
		        
        switch (level) { 
        case 2:
            speed = 50;
            break;
        case 3:
            speed = 10;
            break;
        case 4:
            speed = 20;
            break;
        case 5:
            speed = 15;
            break;
        case 6:
            speed = 10;
            break;
        case 7:
            speed = 9;
            break;
        case 8:
            speed = 8;
            break;
        case 9:
            speed = 8;
            break;
        case 10:
            speed = 8;
            break;
        }
        level_up_on = 0; 

        gotoxy(stat_x_adj, stat_y_level); printf(" LEVEL : %5d", level);
        gotoxy(stat_x_adj, stat_y_goal); printf(" GOAL  : %5d", 10 - cnt);

    }
}
}
}

void reset() {

    level = 1; 
    level_goal = 1000;
    key = 0;
    crush_on = 0;
    cnt = 0;
    speed = 100;

    system("cls"); 
    reset_main(); 
    draw_map(); 
    draw_main(); 

    b_type_next = rand() % 7; 
    new_block();   
}

void check_game_over() {
    int i;

    int x = 5;
    int y = 5;

    for (i = 1; i < Map_w - 2; i++) {
        if (main_org[3][i] > 0) { 
            gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");  
            gotoxy(x, y + 1); printf("▤                              ▤");
            gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
            gotoxy(x, y + 3); printf("▤  |  G A M E  O V E R..   |   ▤");
            gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
            gotoxy(x, y + 5); printf("▤                              ▤");
            gotoxy(x, y + 6); printf("▤  Press any key to restart..  ▤");
            gotoxy(x, y + 7); printf("▤                              ▤");
            gotoxy(x, y + 8); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");

            Sleep(1000);
            while (kbhit()) getch();
            key = getch();
            reset();
        }
        else if(level == 10) { 
            gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");  
            gotoxy(x, y + 1); printf("▤                              ▤");
            gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
            gotoxy(x, y + 3); printf("▤  |  G A M E  O V E R..   |   ▤");
            gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
            gotoxy(x, y + 5); printf("▤                              ▤");
            gotoxy(x, y + 6); printf("▤  Press any key to restart..  ▤");
            gotoxy(x, y + 7); printf("▤                              ▤");
            gotoxy(x, y + 8); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");

            Sleep(1000);
            while (kbhit()) getch();
            key = getch();
            reset();
        }
    }
}

int main() {
    int i;

    srand((unsigned)time(NULL));
    setcursortype(NOCURSOR);
    title();
    reset();

    while (1) {
        for (i = 0; i < 5; i++) {
            check_key();
            draw_main();
            Sleep(speed);
            if (crush_on && check_crush(bx, by + 1, b_rotation) == false) Sleep(100);
            if (space_key_on == 1) {
                space_key_on = 0;
                break;
            }
        }
        drop_block();
        check_level_up();
        check_game_over();
        if (new_block_on == 1) new_block();
        if (level == 2) check_game_over();
    }
}

void pause() {
    int i, j;

    int x = 5;
    int y = 5;

    for (i = 1; i < Map_w - 2; i++) {
        gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
        gotoxy(x, y + 1); printf("▤                              ▤");
        gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
        gotoxy(x, y + 3); printf("▤  |       P A U S E       |   ▤");
        gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
        gotoxy(x, y + 5); printf("▤  Press any key to resume..   ▤");
        gotoxy(x, y + 6); printf("▤                              ▤");
        gotoxy(x, y + 7); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
    }
    getch();

    system("cls");
    reset_main_cpy();
    draw_main();
    draw_map();

    for (i = 1; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(Map_w + Map_w_adj + 3 + j, i + 6);
                printf("■");
            }
            else {
                gotoxy(Map_w + Map_w_adj + 3 + j, i + 6);
                printf("  ");
            }
        }
    }
}



/*타이틀 목록 선택 추가

