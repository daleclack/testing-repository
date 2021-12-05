//http://acm.hdu.edu.cn/showproblem.php?pid=2006

#include <cstdio>

int main(){
    int i,n,x,sum=1;
    while(scanf("%d",&n)!=EOF){
        sum = 1;
        for(i=0;i<n;i++){
            scanf("%d",&x);
            if(x%2==1){
                sum*=x;
            }
        }
        printf("%d\n",sum);
    }
}
