//http://acm.hdu.edu.cn/showproblem.php?pid=2004
#include <cstdio>

int main(int argc,char ** argv){
    int score;
    while (scanf("%d",&score)!=EOF)
    {
        /* code */
        if(score > 100 || score < 0){
            printf("Score is error!\n");
            continue;
        }
        switch (score/10)
        {
        case 10:
        case 9:
            printf("A\n");
            break;
        case 8:
            printf("B\n");
            break;
        case 7:
            printf("C\n");
            break;
        case 6:
            printf("D\n");
            break;
        case 5:
        case 4:
        case 3:
        case 2:
        case 1:
        case 0:
            printf("E\n");
            break;
        }
    }
    return 0;
}