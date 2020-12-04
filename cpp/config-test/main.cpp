#include <stdio.h>

typedef void(*LP)();//transform a function to a pointer

void dale()
{
    printf("cpp43 by dale clack\n");
}

void config()
{
//change content in "config" file
    char str[57];
    printf("Input config:");
    scanf("%s",str);
    freopen("config","w",stdout);
    printf("%s",str);
    fclose(stdout);
}

void test()
{
    char str[57];
    //Read content in "config" file
    freopen("config","r",stdin);
    scanf("%s",str);
    printf("config:%s\n",str);
    fclose(stdin);
}

LP a[]={dale,config,test};

int main(int argc,char *argv[])
{
    int x;
    printf("Input selection:1.change config 2.test\n");
    scanf("%d",&x);
    a[x]();
    return 0;
}
