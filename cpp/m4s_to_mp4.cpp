//This tool is to automatically execute ffmpeg
//Use audio.m4s and video.m4s file to generate a .mp4 file.

#include <iostream>
#include <cstdio>
#include <thread>
#include <cstring>
#include <cstdlib>

int main(int argc,char *argv[]){
    char command[10000],filename1[1000],filename2[1000],output[1000];
    //Get file 1 filename
    printf("Input file1 name:");
    fflush(stdin);
    std::cin.getline(filename1,sizeof(filename1));
    //Get file 2 filename
    printf("Input file2 name:");
    fflush(stdin);
    std::cin.getline(filename2,sizeof(filename2));
    //Get output file name
    printf("Input output name:");
    fflush(stdin);
    std::cin.getline(output,sizeof(output));
    //Generate command and execute the command
    sprintf(command,"ffmpeg -i \"%s\" -i \"%s\" -codec copy \"%s\"",filename1,filename2,output);
    std::thread first (system,command);
    first.detach();
    getchar();
    return 0;
}
