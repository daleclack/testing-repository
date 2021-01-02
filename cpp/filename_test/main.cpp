#include <iostream>
#include <cstdio>
#include <cstring>

typedef void(*pfun)();

void dale(){
    printf("custom filename test by daleclack\n");
}

void write1(){
    getchar();
    char str[57];
    fgets(str,sizeof(str),stdin);
    freopen("test","w",stdout);
    printf("%s",str);
    fclose(stdout);
}

void test(){
    char filename[57],str[57];
    FILE *fp;
    fp=fopen("test","r");
        if(fp==NULL){printf("File not exist!");return ;}
        fgets(str,57,fp);
    fclose(fp);
    sprintf(filename,"xe-%c.x",str[0]);
    fp=fopen(filename,"w");
    fclose(fp);
}

pfun a[]={dale,write1,test};

int main(int argc,char *argv[])
{
    int x;
    printf("1.write content 2.test the custom filename\n");
    scanf("%d",&x);
    a[x]();
    return 0;
}
