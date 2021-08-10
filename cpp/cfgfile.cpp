//A Test to read Config files
// The Config File Should be a text file 
// and the content as follows
// key=value

#include <iostream>
#include <fstream>
#include <string>

typedef void (*pfun)();//The Function Pointer

static bool readCfgFile(const char * cfgfilePath,const std::string &key,std::string &value){
    //Open The Config File
    std::fstream cfgfile;
    cfgfile.open(cfgfilePath);
    if(!cfgfile.is_open()){
        std::cout<<"Failed to open the file!"<<std::endl;
        return false;
    }

    //Read each line of config file and get value
    char tmp[1000];
    while(!cfgfile.eof()){
        cfgfile.getline(tmp,1000);
        std::string line(tmp);
        std::size_t pos = line.find('=');//Get the position of '='

        if(pos == std::string::npos){
            cfgfile.close();
            return false;
        }

        std::string tmpkey=line.substr(0,pos);
        if(tmpkey == key){
            value=line.substr(pos+1);
            cfgfile.close();
            return true;
        }
    }

    cfgfile.close();
    return false;
}

static void readcfg(){
    //Input Config File Path and Key
    char filename[1000];
    std::string cfgkey,cfgvalue;

    std::cout<<"Input Config File Name"<<std::endl;//Config File Name
    std::cin.get();//Clear the cin to read line
    std::cin.getline(filename,1000);

    std::cout<<"Input Config Key"<<std::endl;//Config Key
    std::cin>>cfgkey;

    //Get The Config
    if(readCfgFile(filename,cfgkey,cfgvalue)){
        std::cout<<"The Config Of "<<cfgkey<<" is "<<cfgvalue<<std::endl;
    }else{
        std::cout<<"Failed to Read Config!"<<std::endl;
    }
}

static void appendcfg(){
    //Input Config File Path and Key
    char filename[1000];
    std::string cfgkey,cfgvalue;

    std::cout<<"Input Config File Name"<<std::endl;
    std::cin.get();//Clear the cin to read line
    std::cin.getline(filename,1000);

    //Append Config
    std::fstream cfgfile;
    cfgfile.open(filename,std::ios_base::app);

    if(cfgfile.is_open()){
        std::cout<<"Input Config Key And Config Value"<<std::endl;
        std::cin>>cfgkey>>cfgvalue;
        cfgfile<<cfgkey<<"="<<cfgvalue<<std::endl;
        cfgfile.close();
    }else{
        std::cout<<"Config File Open Failed!"<<std::endl;
    }
}

int main(int argc,char **argv){
    //Function Pointer to select mode
    pfun feature[]={readcfg,appendcfg};
    //Get Selection and execute a mode
    int selection;
    std::cout<<"0.Read a Config 1.Append a Config"<<std::endl<<"Selection a mode:";
    std::cin>>selection;
    feature[selection]();
    return 0;
}
