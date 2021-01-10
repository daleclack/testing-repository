#include <cstdio>

void print(){
    fflush(stdin);
    char str[57];
    fgets(str,sizeof(str),stdin);
    printf("%s\n",str);
}