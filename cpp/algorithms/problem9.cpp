//http://acm.hdu.edu.cn/showproblem.php?pid=2008

#include <cstdio>

int main(){
    int x,y,z,n;
    while(scanf("%d",&n)){
        double temp = 0.0;
        x=0;y=0;z=0;
        if(n==0) break;
        for(int i=0 ; i<n ; i++){
            scanf("%lf",&temp);
            if(temp<0){ x++; }
            if(temp>0){ z++; }
            if(temp==0){ y++; }
        }
        printf("%d %d %d\n",x,y,z);
    }
    return 0;
}
