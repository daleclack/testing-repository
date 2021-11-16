//http://acm.hdu.edu.cn/showproblem.php?pid=2001
#include <cstdio>
#include <cmath>

int main(int argc,char ** argv){
    double x1,y1,x2,y2;
    while(scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2)!=EOF){
        printf("%.2f\n",sqrt(pow(x1-x2,2)+pow(y1-y2,2)));
    }
    return 0;
}