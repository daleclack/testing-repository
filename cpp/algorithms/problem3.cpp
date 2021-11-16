//http://acm.hdu.edu.cn/showproblem.php?pid=2002
#include <cstdio>
#define PI 3.1415927

int main(int argc,char ** argv){
    double r;
    while(scanf("%lf",&r)!=EOF){
        printf("%.3f\n",4.0/3.0*r*r*r*PI);
    }
    return 0;
}