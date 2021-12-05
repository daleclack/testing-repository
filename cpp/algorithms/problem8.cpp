//http://acm.hdu.edu.cn/showproblem.php?pid=2007

#include <cstdio>

int main(){
    int m=0,n=0,x,y;
    while(scanf("%d%d",&m,&n)!=EOF){
        x=0,y=0;
        if(m > n){
            int t = m;
            m = n;
            n = t;
        }
        for(int i=m;i<=n;i++){
            if(i%2==0){
                x += i*i;
            }else{
                y += i*i*i;
            }
        }
        printf("%d %d\n",x,y);
    }
}
