#include <windows.h>
#include <stdio.h>


/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, 
                   HINSTANCE hPrevInstance, LPSTR lpCmdLine, 
                   int nCmdShow) 
{
    char str[20];
    int rel=640;
    sprintf(str,"Xeinit LTS Version:5.2.%d",rel);
	MessageBox(NULL,str,"hello",MB_OK|MB_ICONINFORMATION);
	return 0;
}
