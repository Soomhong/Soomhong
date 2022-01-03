
#include <stdio.h>
#include <stdlib.h>
#include "mtg.h"

/*

	For XP,Vista,Windows 7
	2010.5.29 by clccclcc
*/
/* --------------------------------------------------------------------*/
#ifdef _LINUX_
/* --------------------------------------------------------------------*/
#include <termios.h>
#include <unistd.h>   
#include <string.h>

static struct termios initial_settings, new_settings;
static int peek_character = -1;

void __init_keyboard()
{
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void __close_keyboard()
{
    tcsetattr(0, TCSANOW, &initial_settings);
}

int __kbhit()
{
    unsigned char ch;
    int nread;

    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    if(nread == 1)
    {
        peek_character = ch;
        return 1;
    }
    return 0;
}

char __readch()
{
    char ch;

    if(peek_character != -1)
    {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}
// Key input
char _GetKey()
{
    if(__kbhit())
    {
        return __readch();
    }
    return -1;
}
//////////////////////////////////////////////////////////
// Time control
#include <sys/times.h>
#include <sys/time.h>
long _GetTickCount()
{
    struct timeval ts;

    gettimeofday(&ts,0);
    return (ts.tv_sec * 1000 + (ts.tv_usec / 1000));

}
void _Delay(int time)
{
    usleep(time*1000);
}
/////////////////////////
//draw
#include <curses.h>
WINDOW* g_wnd=NULL;
int g_maxy=0;
int g_maxx=0;

void _BeginWindow()
{
    __init_keyboard();

    g_wnd = initscr(); // curses call to initialize window
    cbreak(); // curses call to set no waiting for Enter key
    noecho(); // curses call to set no echoing
    getmaxyx(g_wnd,g_maxy,g_maxx); // curses call to find size of window
    clear(); // curses call to clear screen, send cursor to position (0,0)
    move(g_maxy,g_maxx);
    refresh(); // curses call to implement all changes since last refresh
}
void _EndWindow()
{
   endwin();
   __close_keyboard();
}
void _DrawText(int x,int y,char* msg)
{
    move(y,x);
    printw("%s",msg);
}
void _Invalidate()
{
    clear();
    Draw();
    move(g_maxy-1,g_maxx-1);
    refresh();
}

void _DrawChar(int x,int y,int key)
{
    move(y,x);
    addch(key);
}
void _ShowCharCode()
{

    clear();

    printw("Upper left corner           "); addch(ACS_ULCORNER); printw(" ACS_ULCORNER\n");
    printw("Lower left corner           "); addch(ACS_LLCORNER); printw(" ACS_LLCORNER\n");
    printw("Lower right corner          "); addch(ACS_LRCORNER); printw(" ACS_LRCORNER\n");
    printw("Tee pointing right          "); addch(ACS_LTEE); printw(" ACS_LTEE\n");
    printw("Tee pointing left           "); addch(ACS_RTEE); printw(" ACS_RTEE\n");
    printw("Tee pointing up             "); addch(ACS_BTEE); printw(" ACS_BTEE\n");
    printw("Tee pointing down           "); addch(ACS_TTEE); printw(" ACS_TTEE\n");
    printw("Horizontal line             "); addch(ACS_HLINE); printw(" ACS_HLINE\n");
    printw("Vertical line               "); addch(ACS_VLINE); printw(" CS_VLINE\n");
    printw("Large Plus or cross over    "); addch(ACS_PLUS); printw(" ACS_PLUS\n");
    printw("Scan Line 1                 "); addch(ACS_S1); printw(" ACS_S1\n");
    printw("Scan Line 3                 "); addch(ACS_S3); printw(" ACS_S3\n");
    printw("Scan Line 7                 "); addch(ACS_S7); printw(" ACS_S7\n");
    printw("Scan Line 9                 "); addch(ACS_S9); printw(" ACS_S9\n");
    printw("Diamond                     "); addch(ACS_DIAMOND); printw(" ACS_DIAMOND\n");
    printw("Checker board (stipple)     "); addch(ACS_CKBOARD); printw(" ACS_CKBOARD\n");
    printw("Degree Symbol               "); addch(ACS_DEGREE); printw(" ACS_DEGREE\n");
    printw("Plus/Minus Symbol           "); addch(ACS_PLMINUS); printw(" ACS_PLMINUS\n");
    printw("Bullet                      "); addch(ACS_BULLET); printw(" ACS_BULLET\n");
    printw("Arrow Pointing Left         "); addch(ACS_LARROW); printw(" ACS_LARROW\n");

    refresh();
    getch();
    clear();
    move(0,0);
    printw("Arrow Pointing Right        "); addch(ACS_RARROW); printw(" ACS_RARROW\n");
    printw("Arrow Pointing Down         "); addch(ACS_DARROW); printw(" ACS_DARROW\n");
    printw("Arrow Pointing Up           "); addch(ACS_UARROW); printw(" ACS_UARROW\n");
    printw("Board of squares            "); addch(ACS_BOARD); printw(" ACS_BOARD\n");
    printw("Lantern Symbol              "); addch(ACS_LANTERN); printw(" ACS_LANTERN\n");
    printw("Solid Square Block          "); addch(ACS_BLOCK); printw(" ACS_BLOCK\n");
    printw("Less/Equal sign             "); addch(ACS_LEQUAL); printw(" ACS_LEQUAL\n");
    printw("Greater/Equal sign          "); addch(ACS_GEQUAL); printw(" ACS_GEQUAL\n");
    printw("Pi                          "); addch(ACS_PI); printw(" ACS_PI\n");
    printw("Not equal                   "); addch(ACS_NEQUAL); printw(" ACS_NEQUAL\n");
    printw("UK pound sign               "); addch(ACS_STERLING); printw(" ACS_STERLING\n");
    refresh();
    getch();


}
void _MessageBox(int x,int y,int w,int h,char* msg)
{
    char key;
    int len=strlen(msg);
    int xpos,ypos;

    WINDOW* new_window_ptr = newwin(h, w, y, x);
    box(new_window_ptr, '|', '-');

    ypos=h/2;
    if( (w -2) < len)
    {
        xpos=1;
    }
    else
    {
        xpos=(w-len)/2;
    }
    mvwprintw(new_window_ptr, ypos, xpos, "%s", msg);
    wrefresh(new_window_ptr);
    //key=getch();
    while(-1 == _GetKey())
    {

    }
}

#endif


/* --------------------------------------------------------------------*/
#ifdef _LINUX1_
/* --------------------------------------------------------------------*/

#include <termios.h>
#include <unistd.h>   
#include <string.h>




//#include <ncurses.h>

static struct termios initial_settings, new_settings;
static int peek_character = -1;

void __init_keyboard()
{
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void __close_keyboard()
{
    tcsetattr(0, TCSANOW, &initial_settings);
}

int __kbhit()
{
    unsigned char ch;
    int nread;

    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    if(nread == 1)
    {
        peek_character = ch;
        return 1;
    }
    return 0;
}

char __readch()
{
    char ch;

    if(peek_character != -1)
    {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}
// Key input
char _GetKey()
{
    if(__kbhit())
    {
        return __readch();
    }
    return -1;
}
//////////////////////////////////////////////////////////
void __clrscr(void)
{
    int i;

    for (i = 0; i < 100; i++)
    // A bunch of new lines for now. It's blank, hey!
    putchar('\n');
}
int __gotoxy(int x, int y)
{

    char essq[100]; // String variable to hold the escape sequence
    char xstr[100]; // Strings to hold the x and y coordinates
    char ystr[100]; // Escape sequences must be built with characters

    /*
    ** Convert the screen coordinates to strings
    */

    sprintf(xstr, "%d", x+1);
    sprintf(ystr, "%d", y+1);

    /*
    ** Build the escape sequence (vertical move)
    */

    essq[0] = '\0';
    strcat(essq, "\033[");
    strcat(essq, ystr);
    /*

    ** Described in man terminfo as vpa=\E[%p1%dd

    ** Vertical position absolute

    */

    strcat(essq, "d");

    /*
    ** Horizontal move
    ** Horizontal position absolute
    */
    strcat(essq, "\033[");
    strcat(essq, xstr);

    // Described in man terminfo as hpa=\E[%p1%dG
    strcat(essq, "G");


    /*
    ** Execute the escape sequence
    ** This will move the cursor to x, y
    */

    printf("%s", essq);



    return 0; 

}

void _DrawText(int x,int y,char* msg)
{
    __gotoxy(x,y);
    puts(msg);
}

void _Invalidate()
{
 
    __clrscr(); 
    Draw();    
}
//////////////////////////////////////////////////////////
// Time control
#include <sys/times.h>
#include <sys/time.h>
long _GetTickCount()
{
    struct timeval ts;

    gettimeofday(&ts,0);
    return (ts.tv_sec * 1000 + (ts.tv_usec / 1000));

}
void _Delay(int time)
{
    usleep(time*1000);
}
// Window
void _BeginWindow()
{
   __init_keyboard();
    __clrscr();
}
void _EndWindow()
{
    __clrscr();
    __close_keyboard();
}
#endif

/*--------------------------------------------------------*/
#ifdef _MSWINDOWS_
/*--------------------------------------------------------*/
#include <windows.h>
#include <conio.h>


	//double buffring
    void __BitBltBuffer();
	void __ClearBuffer();	 
	void __DrawTextBuffer(int x,int y,char* msg);
	void __DrawTextBufferColor(int x,int y,char* msg,int color);
	void __InvalidateBuffer();




///////////////////////////////////////////////////
void _Delay(int time)
{
    Sleep(time);
}

long _GetTickCount()
{
        return GetTickCount();
}
///////////////////////////////////////////////////

/* Standard error macro for reporting API errors */
 #define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

 void _cls()
 {
        HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coordScreen = { 0, 0 };    /* here's where we'll home the
                                                                                cursor */
        BOOL bSuccess;
        DWORD cCharsWritten;
        CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
        DWORD dwConSize;                 /* number of character cells in
                                                                                the current buffer */

        /* get the number of character cells in the current buffer */

        bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
        PERR( bSuccess, "GetConsoleScreenBufferInfo" );
        dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

        /* fill the entire screen with blanks */

        bSuccess = FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
           dwConSize, coordScreen, &cCharsWritten );
        PERR( bSuccess, "FillConsoleOutputCharacter" );

        /* get the current text attribute */

        bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
        PERR( bSuccess, "ConsoleScreenBufferInfo" );

        /* now set the buffer's attributes accordingly */

        bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
           dwConSize, coordScreen, &cCharsWritten );
        PERR( bSuccess, "FillConsoleOutputAttribute" );

        /* put the cursor at (0, 0) */

        bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
        PERR( bSuccess, "SetConsoleCursorPosition" );
        return;
 }

 void _cls1( void )
{
  DWORD n;                         /* Number of characters written */
  DWORD size;                      /* number of visible characters */
  COORD coord = {0};               /* Top left screen position */
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  /* Get a handle to the console */
  HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );

  GetConsoleScreenBufferInfo ( h, &csbi );

  /* Find the number of characters to overwrite */
  size = csbi.dwSize.X * csbi.dwSize.Y;

  /* Overwrite the screen buffer with whitespace */
  FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
  GetConsoleScreenBufferInfo ( h, &csbi );
  FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );

  /* Reset the cursor to the top left position */
  SetConsoleCursorPosition ( h, coord );
}


///////////////////////
char _GetKey()
{
        char key=-1;
        if(kbhit())
        {
                key=getch();
        }

        return key;
}
void _BeginWindow()
{
        CONSOLE_CURSOR_INFO CurInfo;

        CurInfo.dwSize=1;
        CurInfo.bVisible=FALSE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);

        _cls();
}
void _EndWindow()
{
        _cls();
}
void _Invalidate()
{
	__InvalidateBuffer();
	
    //    _cls();
    //    Draw();
}
void _InvalidateBack()
{
	Draw();
	_BitBlt();
}
void _DrawText(int x,int y,char* msg)
{

	__DrawTextBuffer(x,y,msg);
//		DWORD id;
//        COORD co;
//		HANDLE hW;
//        co.X=x;
//        co.Y=y;
        
//		hW=GetStdHandle(STD_OUTPUT_HANDLE);
//        WriteConsoleOutputCharacter(hW,msg,strlen(msg),co,&id);	
}
void _DrawTextColor(int x,int y,char* msg,int color)
{
	__DrawTextBufferColor(x,y,msg,color);
}

void _BitBlt()
{
	__BitBltBuffer();
}

//----------------------------------------Begin Double Buffering ---------
#define SCREEN_WIDTH 80 
#define SCREEN_HEIGHT 25 
CHAR_INFO  g_Buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
int g_TextColor=0x0F; //°ËÀº»ö ¹ÙÅÁ , Èò»ö ±Û¾¾ 
void _SetColor(int color)
{
	g_TextColor=color;
}
void __BitBltBuffer()
{
	HANDLE hOutput = (HANDLE)GetStdHandle( STD_OUTPUT_HANDLE ); 

	COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT }; 
	COORD dwBufferCoord = { 0, 0 }; 
	SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1 }; 

	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH]; 

	ReadConsoleOutput( hOutput, (CHAR_INFO *)buffer, dwBufferSize, 
		dwBufferCoord, &rcRegion ); 

 

	WriteConsoleOutput( hOutput, (CHAR_INFO *)g_Buffer, dwBufferSize, 
		dwBufferCoord, &rcRegion ); 

}
void __ClearBuffer()
{
	int x,y;

	for(y=0;y<25;y++)
	{
		for(x=0;x<80;x++)
		{
			g_Buffer[y][x].Char.AsciiChar=' ';
			g_Buffer[y][x].Attributes=g_TextColor;
		}
	}
	g_Buffer[24][79].Char.AsciiChar='\0';
}
void __DrawTextBuffer(int x,int y,char* msg)
{
	int i;

	for(i=0;i<strlen(msg);i++)
	{
		g_Buffer[y][x+i].Char.AsciiChar=msg[i];
		g_Buffer[y][x+i].Attributes=g_TextColor;
	}
}
void __DrawTextBufferColor(int x,int y,char* msg,int color)
{
	int i;

	for(i=0;i<strlen(msg);i++)
	{
		g_Buffer[y][x+i].Char.AsciiChar=msg[i];
		g_Buffer[y][x+i].Attributes=color;
	}
}
void __InvalidateBuffer()
{	
	__ClearBuffer();	
	Draw();
	_BitBlt();

}
//--------------------------------------End Duble Buffering...---------------------------
 
void _DrawTextOrg(int x,int y,char* msg)
{

		DWORD id;
        COORD co;
		HANDLE hW;
        co.X=x;
        co.Y=y;
        
		hW=GetStdHandle(STD_OUTPUT_HANDLE);
        WriteConsoleOutputCharacter(hW,msg,strlen(msg),co,&id);	
}
void _DrawTextColorOrg(int x,int y,char* msg,int color)
{
		CONSOLE_SCREEN_BUFFER_INFO   BufInfo;
		COORD Coor;

		DWORD id;
        COORD co;
		HANDLE hW;
        co.X=x;
        co.Y=y;
        
		hW=GetStdHandle(STD_OUTPUT_HANDLE);

		GetConsoleScreenBufferInfo(hW,&BufInfo);
	    Coor.X=BufInfo.dwCursorPosition.X;
	    Coor.Y=BufInfo.dwCursorPosition.Y;


        WriteConsoleOutputCharacter(hW,msg,strlen(msg),co,&id);	

		FillConsoleOutputAttribute(hW,color,strlen(msg),co,&id);


}
 
void _MessageBox(int x,int y,int w,int h,char* msg)
{
        char key;
        int tx,ty;
        int len=(w-strlen(msg))/2;

        for(tx=0;tx<w;tx++)
        {
                _DrawTextOrg(x+tx,y,"-");
        }

        for(tx=0;tx<w;tx++)
        {
                _DrawTextOrg(x+tx,y+h,"-");
        }

        for(ty=0;ty<h;ty++)
        {
                _DrawTextOrg(x,y+ty,"|");
        }

        for(ty=0;ty<h;ty++)
        {
                _DrawTextOrg(x+w,y+ty,"|");
        }
        _DrawTextOrg(x+len,y+h/2,msg);
        key=getch();
}
void _MessageBoxEx(int x,int y,int w,int h,char* msg)
{	
	int loop_len;
	int loop;
	int index;
	int d_index;

	char line[2048];
	char key;
	int tx,ty;
	int len=(w-strlen(msg))/2;

	int x_start; // x + (len - strlen(line)/2)

	for(tx=0;tx<w;tx++)
	{
		_DrawTextOrg(x+tx,y,"-");
	}

	for(tx=0;tx<w;tx++)
	{
		_DrawTextOrg(x+tx,y+h,"-");
	}

	for(ty=0;ty<h;ty++)
	{
		_DrawTextOrg(x,y+ty,"|");
	}

	for(ty=0;ty<h;ty++)
	{
		_DrawTextOrg(x+w,y+ty,"|");
	}
	///////////////////////////
	loop_len=1;
	index=0;
	while(1)
	{
		if('\n'==msg[index])
		{
			loop_len++;
		}
		if('\0'==msg[index])
		{
			break;
		}
		index++;
	}
	loop=0;
	index=0;
	d_index=0;
	while(1)
	{
		if('\n'==msg[index])
		{
			line[d_index]='\0';
			d_index=0;
			_DrawTextOrg(x + (w/2 - strlen(line)/2),y+(h/2-loop_len/2)+ loop,line);
			loop++;
			index +=1;		
		}
		else if('\0'==msg[index])
		{
			line[d_index]='\0';
			_DrawTextOrg(x + (w/2 - strlen(line)/2),y+(h/2-loop_len/2)+ loop,line);
			break;
		}
		else 
		{
			line[d_index]=msg[index];			
			d_index++;
			index++;		
		}
			
	}

	key=getch();
}
void _MessageBoxColor(int x,int y,int w,int h,char* msg,int color)
{
        char key;
        int tx,ty;
        int len=(w-strlen(msg))/2;

        for(tx=0;tx<w;tx++)
        {
                _DrawTextColorOrg(x+tx,y,"-",color);
        }

        for(tx=0;tx<w;tx++)
        {
                _DrawTextColorOrg(x+tx,y+h,"-",color);
        }

        for(ty=0;ty<h;ty++)
        {
                _DrawTextColorOrg(x,y+ty,"|",color);
        }

        for(ty=0;ty<h;ty++)
        {
                _DrawTextColorOrg(x+w,y+ty,"|",color);
        }
        _DrawTextColorOrg(x+len,y+h/2,msg,color);
        key=getch();
}
void _MessageBoxExColor(int x,int y,int w,int h,char* msg,int color)
{	
	int loop_len;
	int loop;
	int index;
	int d_index;

	char line[2048];
	char key;
	int tx,ty;
	int len=(w-strlen(msg))/2;

	int x_start; // x + (len - strlen(line)/2)

	for(tx=0;tx<w;tx++)
	{
		_DrawTextColorOrg(x+tx,y,"-",color);
	}

	for(tx=0;tx<w;tx++)
	{
		_DrawTextColorOrg(x+tx,y+h,"-",color);
	}

	for(ty=0;ty<h;ty++)
	{
		_DrawTextColorOrg(x,y+ty,"|",color);
	}

	for(ty=0;ty<h;ty++)
	{
		_DrawTextColorOrg(x+w,y+ty,"|",color);
	}
	///////////////////////////
	loop_len=1;
	index=0;
	while(1)
	{
		if('\n'==msg[index])
		{
			loop_len++;
		}
		if('\0'==msg[index])
		{
			break;
		}
		index++;
	}
	loop=0;
	index=0;
	d_index=0;
	while(1)
	{
		if('\n'==msg[index])
		{
			line[d_index]='\0';
			d_index=0;
			_DrawTextColorOrg(x + (w/2 - strlen(line)/2),y+(h/2-loop_len/2)+ loop,line,color);
			loop++;
			index +=1;		
		}
		else if('\0'==msg[index])
		{
			line[d_index]='\0';
			_DrawTextColorOrg(x + (w/2 - strlen(line)/2),y+(h/2-loop_len/2)+ loop,line,color);
			break;
		}
		else 
		{
			line[d_index]=msg[index];			
			d_index++;
			index++;		
		}
			
	}

	key=getch();
}

#endif

