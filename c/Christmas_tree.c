#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void SetColor(int Mode){
    //Get Color
    int color = rand()%16;
    if(color == 0 ) color = 0x04;

    //Set Color for Console
    HANDLE  hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    if(Mode == 0){
        SetConsoleTextAttribute(hCon,FOREGROUND_GREEN);
    }else{
        SetConsoleTextAttribute(hCon,color);
    }
}

#define PI 3.14159265359

float sx,sy;

float sdCircle(float px,float py,float r){
    float dx = px - sx, dy = py-sy;
    return sqrtf(dx * dx + dy * dy) - r;
}

float opUnion(float d1,float d2){
    return d1 < d2 ? d1 : d2;
}

#define T px + scale * r * cosf(theta), py + scale * r * sin(theta)

float f(float px, float py, float theta, float scale, int n){
    float d = 0.0f;
    for(float r = 0.0f; r < 0.8f; r += 0.02f){
        d = opUnion(d,sdCircle(T, 0.05f * scale * (0.95f - r)));
    }

    if(n > 0){
        for(int t = -1; t <=1; t+=2){
            float tt = theta + t * 1.8f;
            float ss = scale * 0.9f;
            for(float r = 0.2f; r < 0.8f; r += 0.1f){
                d = opUnion(d, f(T, tt, ss*0.5f, n-1));
                ss *= 0.8f;
            }
        }
    }
}

int main(int argc, char * argv[]){
    srand((unsigned)time(NULL));
    int n = argc > 1 ? atoi(argv[1]) : 3;

    int SetCnt = 0;
    int CntTotal = 0;
    float fReverseCnt = 0;
    int ColorIndex = 0;
    
    for(sy = 0.8f; sy > 0.0f; sy -= 0.02f, putchar('\n') ){
        ColorIndex++;

        SetCnt = 0;

        for(sx = -0.35f; sx < 0.35f; sx += 0.01f){
            if(f(0, 0, PI * 0.5f, 1.0f, n) < 0){
                if(ColorIndex%5 == 0 ){
                    SetColor(1);
                }else{
                    if(SetCnt < 3){
                        SetCnt++;
                        SetColor(1);

                        fReverseCnt = sx + 0.01f;
                    }else if(sx >= fabs(fReverseCnt)){
                        SetColor(1);
                    }else{
                        SetColor(0);
                    }
                }
                putchar(' ');
            }else{
                putchar(' ');
            }
        }
    }

    return 0;
}
