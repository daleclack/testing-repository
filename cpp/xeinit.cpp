#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	for(;;){
	int a=0,b;
	a=rand();
	b=a;
	a%=2;
	printf("%d %d\n",a,b);
	//getchar();
	}
	return 0;
}
