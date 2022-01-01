/* 
 * File:   clccclcc_tg3.h
 * Author: clccclcc
 *
 * Copyright(R) 2017 by clccclcc
 */


#ifndef _CLCCCLCC_TG2_1_H
#define	_CLCCCLCC_TG2_1_H

#ifdef	__cplusplus
extern "C" {
#endif
    


     //#define _LINUX_  //curses =>$ gcc -o game *.c  -lncurses
     //#define _LINUX1_ // standard c => gcc -o game *.c 
     #define _MSWINDOWS_ // consol api

    
    // Window 

    void _BeginWindow();
    void _EndWindow();
#ifdef _MSWINDOWS_
	void _SetColor(int color);
#endif

	void _DrawText(int x,int y,char* msg);
	void _Invalidate();

#ifdef _MSWINDOWS_
	void _InvalidateBack();
	void _DrawTextOrg(int x,int y,char* msg);
	void _DrawTextColorOrg(int x,int y,char* msg,int color);
	void _DrawTextColor(int x,int y,char* msg,int color); 
	void _BitBlt();
#endif
    extern void Draw();


    
    // Key 
    char _GetKey();

    // Time control
    long _GetTickCount();
    void _Delay(int time);

	// messagebox 
	void _MessageBox(int x,int y,int w,int h,char* msg);
#ifdef _MSWINDOWS_
	void _MessageBoxEx(int x,int y,int w,int h,char* msg);
	void _MessageBoxColor(int x,int y,int w,int h,char* msg,int color);
	void _MessageBoxExColor(int x,int y,int w,int h,char* msg,int color);
#endif

	// OS Special Functions
#ifdef _LINUX_
    void _DrawChar(int x,int y,int key);
    void _ShowCharCode();    
#endif
 
 

#ifdef	__cplusplus
}
#endif

#endif	/* _CLCCCLCC_TG3_H */

/*
    API History

	For XP,Vista,Windows 7
	2010.6.15 by clccclcc

    - double buffering 지원
	- 텍스트 컬러(배경,글자색) 출력함수 지원 _DrawTextColor()
	- 전체 콘솔의 컬러 지정 : _SetColor(0xf1)
	
*/


