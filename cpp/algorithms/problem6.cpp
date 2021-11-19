//http://acm.hdu.edu.cn/showproblem.php?pid=2004
#include <cstdio>

int main(int argc,char ** argv){
    int year,month,day,sum_day=0;
    while (scanf("%d/%d/%d",&year,&month,&day)!=EOF)
    {
        switch(month){
            case 1:
                sum_day+=31;
                break;
            case 2:
                if(month%4 == 0 && month%100 != 0){
                    sum_day += 60;
                }else{
                    sum_day += 59;
                }
                break;
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
        }
    }
    return 0;
}