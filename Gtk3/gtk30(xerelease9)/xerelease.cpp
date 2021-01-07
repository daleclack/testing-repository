#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include"xeapi.h"

//typedef void(*LP)(struct tm *local);//define a  pointer function

int total_day(int year,int month,int day)
{
    //Calculate day of 1 year
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

void dale(struct tm *local)
{
	printf("xeinit release maker by dale\n");
}

void longterm(struct tm *local,char lts[],char *str)
{
    char filename[57];
    sprintf(filename,"xe-%c.x",lts[0]);
	int lts_ver=0;//release version
	int year1=2019,month1=1,day1=11,year2=local->tm_year+1900,month2=local->tm_mon+1,day2=local->tm_mday;
	lts_ver=total_year_day(year1,year2)-total_day(year1,month1,day1)+total_day(year2,month2,day2);//get release version
    sprintf(str,"Xeinit LTS version:%s.%d\n",lts,lts_ver);
	freopen(filename,"a",stdout);//put all output in xe-release file
    printf("%d-%d-%d ",local->tm_year+1900,local->tm_mon+1,local->tm_mday);//output:release branch time in xe-release
    printf("%s.%d Api:%d\n",lts,lts_ver,xeapi1(local));
    fclose(stdout);
    return ;
}

void stable(struct tm *local,char rel[],char *str)
{
    char filename[57];
    sprintf(filename,"xe-%c.x",rel[0]);
	int devel1;//stable release version
	int year1=2017,month1=6,day1=17,year2=local->tm_year+1900,month2=local->tm_mon+1,day2=local->tm_mday;
	devel1=total_year_day(year1,year2)-total_day(year1,month1,day1)+total_day(year2,month2,day2);//get release version
    sprintf(str,"Xeinit stable Version:%s.%d\n",rel,devel1);
    freopen(filename,"a",stdout);
    printf("%d-%d-%d ",local->tm_year+1900,local->tm_mon+1,local->tm_mday);//output:development branch time in xe-release
    printf("%s.%d Api:%d\n",rel,devel1,xeapi1(local));
    fclose(stdout);
    return ;
}

void develop(struct tm *local,char devel[],char *str){
    char filename[57];
    sprintf(filename,"xe-%c.x",devel[0]);
    int devel1;//development version
	int year1=2017,month1=6,day1=17,year2=local->tm_year+1900,month2=local->tm_mon+1,day2=local->tm_mday;
	devel1=total_year_day(year1,year2)-total_day(year1,month1,day1)+total_day(year2,month2,day2);//get release version
    sprintf(str,"Xeinit devel Version:%s.%d\n",devel,devel1);
    freopen(filename,"a",stdout);
    printf("%d-%d-%d ",local->tm_year+1900,local->tm_mon+1,local->tm_mday);//output:development branch time in xe-release
    printf("%s.%d Api:%d\n",devel,devel1,xeapi1(local));
    fclose(stdout);
    return ;
}
