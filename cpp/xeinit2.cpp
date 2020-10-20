#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int a=0,b;
	printf("Press Ctrl+C to stop");
	for(;;){
	a=rand();
	b=a;
	a%=2;
	//getchar();
	}
	printf("%d %d",a,b);
	return 0;
}
