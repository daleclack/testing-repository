#include <iostream>
#include <cstdio>
#include <cstring>

int main(int argc,char *argv[])
{ 
    int a,num1,result1;
    if(argc<2){
	    std::cout<<"usage:"<<argv[0]<<" [circulate number]"<<std::endl;
    }else{
    /*std::cout<<"argc="<<argc<<std::endl;
    for(int i=0;i<argc;i++){
        std::cout<<"argv["<<i<<"]="<<argv[i]<<std::endl;
  }
    a=strlen(argv[1]);
    for(int i=0;i<a;i++){
        std::cout<<*argv[1]<<std::endl;
    }*/
    a=atoi(argv[1]);
    for(int i=0;i<a;i++){
        num1=rand();
	}
	result1=num1%2;
	std::cout<<result1<<" "<<num1<<std::endl;
    }
    return 0;
}
