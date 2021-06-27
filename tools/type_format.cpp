#include <iostream>
#include <cstring>
#include <cstdio>

int main(){
    char filename[512],filename1[512],extbuf[512];
    std::cin.getline(filename,512);
    std::cin.getline(filename1,512);
    FILE *fp,*outfp;
    fp=fopen(filename,"rt+");
    outfp=fopen(filename1,"wt+");
    if(fp!=NULL){
        fprintf(outfp,"static const char * const supported_globs[]={\n");
        while(fscanf(fp,"%s",extbuf)!=EOF){
            fprintf(outfp,"\t\"*.%s\",\n",extbuf);
        }
        fprintf(outfp,"NULL\n};\n");
    }else{
        std::cout<<"Error!"<<std::endl;
    } 
    return 0;
}
