//http://acm.hdu.edu.cn/showproblem.php?pid=2000
#include <cstdio>

void sort_and_output(char * str){
    for(int i=0;i<3;i++){
        for(int j=i+1;j<3;j++){
            if(str[i]>str[j]){
                char tmp=str[j];
                str[j]=str[i];
                str[i]=tmp;
            }
        }
    }
    printf("%c %c %c\n",str[0],str[1],str[2]);
}

int main(int argc,char ** argv){
    char str[3];
    while(scanf("%s",str)!=EOF){
        sort_and_output(str);
    }
    return 0;
}