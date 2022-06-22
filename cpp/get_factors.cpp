#include <iostream>
#include <cstdio>
#include <string>

static int pos = 0;

void get_factors(const char * factor){
    double result1 = 0.0, result2 = 0.0;
    char c = factor[pos];
    while(isdigit(c)){
        result1 = result1 * 10 + c -'0';
        pos++;
        c = factor[pos];
    }
    if(c == '.'){
        pos++;                  //Pass the point
        c = factor[pos];        //Get numbers
        while(isdigit(c)){      //Transfer chars to number
            result2 = result2 * 0.1 + (c - '0') * 0.1;
        }
    }
    printf("%f\n",result1 + result2);
}

int main(int argc,char ** argv){
    char buf[57];
    std::cin.getline(buf,sizeof(buf));
    std::cout<<buf<<std::endl;
    get_factors(buf);
    return 0;
}
