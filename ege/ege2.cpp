#include<graphics.h>
#include<cstdio>
int main(){
	initgraph(400,300);//create a wimdow
    setfont(16,0,"SimSum");//set font and size
    for(;is_run();dely_fps(60)){
    	cleardevice();//cls
	    int x,y;
	    char str[30];
	    mousepos(&x,&y);//get mouse  position
	    sprintf(str,"%4d %4d",x,y);//transform to string
	    outtextxy(0,0,str);
	}
	closegraph();
	return 0;
}
