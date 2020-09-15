#include<cstdio>
#include<graphics.h>
using namespace std;
int main(){
	initgraph(480,360);
	setfont(18,0,"SimSum");
	mouse_msg msg={0};
	for(;is_run();delay_fps(60)){
		while(mousemsg()){
			msg=getmouse();
		}
		cleardevice();
		xyprintf(0,0,"x=%10d y=%10d",msg.x,msg.y);
		xyprintf(0,20,"move=%d down=%d up=%d",(int)msg.is_move(),(int)msg.is_down(),(int)msg.is_up());
		xyprintf(0,40,"left=%d right=%d mid=%d",(int)msg.is_left(),(int)msg.is_right(),(int)msg.is_mid());
		xyprintf(0,60,"wheel=%d wheel rotare=%d",(int)msg.is_wheel(),msg.wheel);
	}
	closegraph();
	return 0;
}
