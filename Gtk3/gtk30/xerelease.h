int total_day(int year,int month,int day);

int total_year_day(int year1,int year2);

void dale(struct tm *local);

void longterm(struct tm *local,const char *lts,char *str);

void stable(struct tm *local,const char *devel,char *str);

void develop(struct tm *local,const char *devel,char *str);
