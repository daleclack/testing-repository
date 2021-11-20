//http://acm.hdu.edu.cn/showproblem.php?pid=2005
#include <cstdio>

int main(int argc,char ** argv){
    int year,month,day,sum_day=0;
    while (scanf("%d/%d/%d",&year,&month,&day)!=EOF)
    {
        sum_day=0;
        switch(month){
            case 1:
                sum_day = day;
                break;
            case 2:
                sum_day = 31+day;
                break;
            case 3:
                sum_day = 59+day;
                break;
            case 4:
                sum_day = 90+day;
                break;
            case 5:
                sum_day = 120+day;
                break;
            case 6:
                sum_day = 151+day;
                break;
            case 7:
                sum_day = 181+day;
                break;
            case 8:
                sum_day = 212+day;
                break;
            case 9:
                sum_day = 243+day;
                break;
            case 10:
                sum_day = 273+day;
                break;
            case 11:
                sum_day = 304+day;
                break;
            case 12:
                sum_day = 334+day;
                break;
        }
        if(year%4 == 0 && year%100 != 0 && month > 2){
            sum_day += 1;
        }
        printf("%d\n",sum_day);
    }
    return 0;
}