#include <iostream>
#include <cstdio>
#include <cstdlib>

int main(int argc,char *argv[])
{ 
	int x;
	srand((unsigned)time(NULL));
	x=rand();
	std::cout<<x%2<<" "<<x<<std::endl;
	return 0;
}
