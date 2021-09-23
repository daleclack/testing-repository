#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char **argv){
    const char * src = *argv;
    int len = strlen(src); //argv[0]
    char * tmp = malloc(len);
#ifdef _WIN32
    strncpy(tmp,src,len-8);
    tmp[len-8]='\0';
#else
    strncpy(tmp,src,len-4);
    tmp[len-4]='\0';
#endif
    printf("%s\n",tmp);
    free(tmp);
    return 0;
}
