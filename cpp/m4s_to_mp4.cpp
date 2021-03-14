#include <cstdio>
#include <thread>
#include <cstring>
#include <cstdlib>

void clear(char str[]){
    if(strlen(str)==0) return;
    int i=0;
    while(str[i]!='\n'){
        i++;
    }
    str[i]='\0';
}

int main(int argc,char *argv[]){
    char command[10000],filename1[1000],filename2[1000],output[1000];
    printf("Input file1 name:");
    fflush(stdin);
    fgets(filename1,sizeof(filename1),stdin);
    clear(filename1);
    printf("Input file2 name:");
    fflush(stdin);
    fgets(filename2,sizeof(filename2),stdin);
    clear(filename2);
    printf("Input output name:");
    fflush(stdin);
    fgets(output,sizeof(output),stdin);
    clear(output);
    //printf("%s\n%s",filename1,filename2);
    sprintf(command,"ffmpeg -i \"%s\" -i \"%s\" -codec copy \"%s\"",filename1,filename2,output);
    //printf("%s",command);
    std::thread first (system,command);
    first.detach();
    getchar();
    return 0;
}
