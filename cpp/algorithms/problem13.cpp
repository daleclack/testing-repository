//http://acm.hdu.edu.cn/showproblem.php?pid=2012

#include <stdio.h>
#include <math.h>

int isPrime(int number){
    int i;
    for(i=2;i<=sqrt(number);i++){
        if(number%i==0) return 0;
    }
    return 1;
}

int main(){
    int x,y,i,flag=1;
    while(scanf("%d%d",&x,&y)){
        flag=1;
        if(x==0 && y==0){break;}
        if(x>y){
            int t=x;
            x=y;
            y=t;
        }
        for(i=x;i<=y;i++){
            if(!isPrime(i*i+i+41)){
                flag=0;
                break;
            }
        }
        if(flag){ printf("OK\n"); }
        else{ printf("Sorry\n"); }
    }
    return 0;
}
