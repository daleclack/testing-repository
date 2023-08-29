#include <cstdio>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include "timer.h"

// typedef void(*LP)(struct tm *local);//define a  pointer function
#define MAX_PATH 260

int total_day(int year, int month, int day)
{
    // Calculate day of 1 year
    int sum = 0;
    switch (month)
    {
    case 1:
        sum = day;
        break;
    case 2:
        sum = day + 31;
        break;
    case 3:
        sum = day + 59;
        break;
    case 4:
        sum = day + 90;
        break;
    case 5:
        sum = day + 120;
        break;
    case 6:
        sum = day + 151;
        break;
    case 7:
        sum = day + 181;
        break;
    case 8:
        sum = day + 212;
        break;
    case 9:
        sum = day + 243;
        break;
    case 10:
        sum = day + 273;
        break;
    case 11:
        sum = day + 304;
        break;
    case 12:
        sum = day + 334;
        break;
    default:
        printf("Date Wrong!");
    }
    if (year % 4 == 0 && year % 100 != 0)
        sum = sum + 1;
    return sum;
}

int total_year_day(int year1, int year2)
{
    // Calculate day of years
    int sum = 0;
    sum = (year2 - year1) * 365;
    for (int i = year1; i < year2; i++)
    {
        if (i % 4 == 0 && i % 100 != 0)
        {
            sum = sum + 1;
        }
    }
    return sum;
}

int get_time_duration(int year, int month, int day)
{
    // Get Current time
    time_t t;
    t = time(NULL);
    struct tm *local;
    local = localtime(&t);

    // Calculate duration
    int duration_day = total_year_day(year, local->tm_year + 1900) 
        + total_day(year, month, day) 
        - total_day(local->tm_year + 1900, local->tm_mon + 1, local->tm_mday);

    return duration_day;
}
