#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char **argv){
    const char * src = *argv;
    int len = strlen(src); //argv[0]
    char * tmp = malloc(len);
    strncpy(tmp,src,len-4);
    printf("%s\n",tmp);
    free(tmp);
    return 0;
}
