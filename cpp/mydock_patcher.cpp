#include <windows.h>
#include <iostream>

#define INI_PATH "Y:\\test.ini"

int main(int argc, char **argv){
    char tmp1[30]={}, tmp2[30]={};
    GetPrivateProfileString("iconame", "explorer", "", tmp1, sizeof(tmp1), INI_PATH);
    GetPrivateProfileString("menu", "newfinderwindow", "", tmp2, sizeof(tmp2), INI_PATH);
    std::cout << tmp1 << std::endl;
    std::cout << tmp2 << std::endl;
    WritePrivateProfileString("iconame", "explorer", "访达", INI_PATH);
    WritePrivateProfileString("menu", "newfinderwindow", "新建访达窗口", INI_PATH);
    system("pause");
    return 0;
}