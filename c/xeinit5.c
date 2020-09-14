#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
int total_day(int year,int month,int day){//Calculate day of 1 year
	int sum=0;
	switch(month){
		case 1:
			sum=day;break;
		case 2:
			sum=day+31;break;
		case 3:
			sum=day+59;break;
		case 4:
			sum=day+90;break;
		case 5:
			sum=day+120;break;
		case 6:
			sum=day+151;break;
		case 7:
			sum=day+181;break;
		case 8:
			sum=day+212;break;
		case 9:
			sum=day+243;break;
		case 10:
			sum=day+273;break;
		case 11:
			sum=day+304;break;
		case 12:
			sum=day+334;break;
		default:
			printf("Date Wrong!");
	}
	if(year%4==0&&year%100!=0) sum=sum+1;
	return sum;
}
int total_year_day(int year1,int year2){//Calculate day of years
	int sum=0;
	sum=(year2-year1)*365;
	for(int i=year1;i<year2;i++){
		if(i%4==0&&i%100!=0){
			sum=sum+1;
		}
	}
	return sum;
}
int main(){
	struct tm *local;
    time_t t;
    t=time(NULL);
    local=localtime(&t);//Get local time
	int year1=2019,month1=1,day1=11;
	int year2=local->tm_year+1900,month2=local->tm_mon+1,day2=local->tm_mday;
	int sum_day=0;
	sum_day=total_year_day(year1,year2)-total_day(year1,month1,day1)+total_day(year2,month2,day2);
	printf("Xeinit developed:%d Days\n",sum_day);
	system("pause");
	return 0;
}
