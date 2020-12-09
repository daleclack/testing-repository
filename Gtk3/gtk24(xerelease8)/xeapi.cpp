#include"xeapi.h"
int xeapi1(struct tm *local){
	int year1=2019,month1=6,apiver=0;
	int year2=local->tm_year+1900,month2=local->tm_mon+1;
	//printf("%d %d",year1,year2);
	apiver=(year2-year1)*12-month1+month2+22;
	if(local->tm_mday<7) apiver--;
	return apiver;
}
