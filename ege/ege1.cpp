#include<graphics.h>
int main(){
    initgraph(320,240);//Create A Window sized 320x240 
	setviewport(100,40,240,220,1);//set text area (100,40) to (240,220)
	setcolor(EGERGB(0x0,0xFF,0x0));//window color
	setfontbkcolor(RGB(0x80,0x00,0x80));//font background color
	setfont(17,0,"Simsum");//Set Font
	outtextxy(0,0,"Hello EGE Graphics");//output text at specific place
	setbkmode(TRANSPARENT);
	outtextxy(0,20,"Hello EGE Graphics");//output text at specific place
	setviewport(0,0,getwidth(),getheight(),1);//reset text area
	outtextxy(0,0,"Hello EGE Graphics");
	getch();
	closegraph();
	return 0;
}
