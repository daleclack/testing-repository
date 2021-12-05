//http://acm.hdu.edu.cn/showproblem.php?pid=2011

#include <cstdio>
#include <cmath>

int main(){
    int m,n;
    double sum;
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        scanf("%d",&n);
        sum=0.0;
        for(int j=1;j<=n;j++){
            sum+=1.0/(double)j*pow(-1,j-1);
        }
        printf("%.2f\n",sum);
    }
    return 0;
}
