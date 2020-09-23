#include<stdio.h>
#include<graphics.h>
int main(){
	initgraph(400,300);
	setbkcolor(BLUE);
	setcolor(BLACK);
	setfont(12,0,"SimSum");
	setbkmode(TRANSPARENT);
	outtextxy(40,90,"Text1");
	setfillcolor(BLACK);
	bar(0,0,70,20);
	setcolor(WHITE);
	setfont(15,0,"SimSum");
	setbkmode(TRANSPARENT);
	rectprintf(0,0,60,15,"Text2");
	getch();
	return 0;
}
