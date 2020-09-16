#include<graphics.h>
#include<stdio.h>
int main(){
	initgraph(400,300);
	setcolor(GREEN);
	line(0,100,370,350);
	setfillcolor(EGERGB(0xff,0x00,0x80));
	bar(30,0,70,20);
	setcolor(RED);
	arc(40,70,0,124,13);
	getch();
	closegraph();
	return 0;
}
