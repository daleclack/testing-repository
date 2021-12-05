//http://acm.hdu.edu.cn/showproblem.php?pid=2010

#include <cstdio>

int main(){
    int m,n;
    bool flag;
    while(scanf("%d%d",&m,&n)!=EOF){
        flag = false;
        if(m>n){
            int t = m;
            m = n;
            n = t;
        }
        for(int i=m;i<=n;i++){
            int x,y,z;
            x = i/100;
            y = i%100/10;
            z = i%10;
            if(x*x*x + y*y*y + z*z*z == i){
                if(flag){ printf(" "); }
                printf("%d",i);
                flag = true;
            }
        }
        if(!flag){
            printf("no\n");
        }else{
            printf("\n");
        }
    }
    return 0;
}
