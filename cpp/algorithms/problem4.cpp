//http://acm.hdu.edu.cn/showproblem.php?pid=2003
#include <cstdio>

int main(int argc,char ** argv){
    double x;
    while(scanf("%lf",&x)!=EOF){
        printf("%.2f\n",x>0?x:-x);
    }
    return 0;
}