#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstring>
using namespace std;
typedef void(*LP)(struct tm *local);//define a  pointer function
void dale(struct tm *local){
	cout<<"xeinit release maker by dale"<<endl;
}
void release(struct tm *local){
	string rel;//release version
	cout<<"xeinit release version:";
    cin>>rel;//get release version
    freopen("xe-release","a",stdout);//put all output in xe-release file
    printf("%d-%d-%d ",local->tm_year+1900,local->tm_mon+1,local->tm_mday);//output:release branch time in xe-release
    cout<<rel<<endl;
    fclose(stdout);
    return ;
}
void develop(struct tm *local){
	string devel;//development version
	cout<<"xeinit development version:";
    cin>>devel;//get development version
    freopen("xe-development","a",stdout);
    printf("%d-%d-%d ",local->tm_year+1900,local->tm_mon+1,local->tm_mday);//output:development branch time in xe-release
    cout<<devel<<endl;
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
    cout<<"Input branch:1.release 2.development"<<endl;
    cin>>x;
    a[x](local);
    return 0;
}
