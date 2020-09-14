#include<stdio.h>
#include<time.h>
#include<string.h>
typedef void(*LP)(struct tm *local);//define a  pointer function
void dale(struct tm *local){
	printf("xeinit release maker by dale\n");
}
void release(struct tm *local){
	char rel[57];//release version
	printf("xeinit 5 version:");
    scanf("%s",&rel);//get release version
    freopen("xe-5.x","a",stdout);//put all output in xe-release file
    printf("%d-%d-%d ",local->tm_year+1900,local->tm_mon+1,local->tm_mday);//output:release branch time in xe-release
    printf("%s\n",rel);
    fclose(stdout);
    return ;
}
void develop(struct tm *local){
	char devel[57];//development version
	printf("xeinit 6 version:");
    scanf("%s",&devel);//get development version
    freopen("xe-6.x","a",stdout);
    printf("%d-%d-%d ",local->tm_year+1900,local->tm_mon+1,local->tm_mday);//output:development branch time in xe-release
    printf("%s\n",devel);
    fclose(stdout);
    return ;
}
int main(int argc, char **argv) {
    struct tm *local;
    time_t t;
    t=time(NULL);
    local=localtime(&t);//Get local time
    LP a[]={dale,release,develop};
    int x;
    printf("Input branch:1.release 2.development\n");
    scanf("%d",&x);
    a[x](local);
    return 0;
}
