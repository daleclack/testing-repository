//http://acm.hdu.edu.cn/showproblem.php?pid=2009

#include <cstdio>
#include <cmath>

int main(){
    int m;
    double n;
    while(scanf("%lf%d",&n,&m)!=EOF){
        double sum = 0;
        for(int i=0;i<m;i++){
            sum += n;
            n=sqrt(n);
        }
        printf("%.2f\n",sum);
    }
    return 0;
}
