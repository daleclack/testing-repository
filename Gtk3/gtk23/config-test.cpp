#include "config-test.h"

void dale(const char str[])
{
    printf("cpp43 by dale clack\n");
}

void config(const char str[])
{
//change content in "config" file
    /*char str[57];
    printf("Input config:");
    scanf("%s",str);*/
    freopen("config","w",stdout);
    printf("%s",str);
    fclose(stdout);
}

void test(char *str)
{
    char str_tmp[57];
    //Read content in "config" file
    freopen("config","r",stdin);
    scanf("%s",str_tmp);
    //printf("config:%s\n",str);
    fclose(stdin);
    strcpy(str,str_tmp);
}

