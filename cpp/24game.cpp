#include <iostream>
#include <string>
#include <ctime>

//生成在[begin,end]范围内的随机数
double randnum(int begin = 0, int end = 1){
    srand(time(NULL));
    return (rand()%(end-begin+1))+begin;
}

//24点主类
class Game24{};

int main(int argc, char ** argv){
    printf("%f",randnum(1,13));
    return 0;
}