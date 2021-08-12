// A Test to read Config files
// This is a modified version
// The Config File Should be a text file 
// and the content as follows
// key=value

#include "cfgfile.hh"

static void Trim(std::string &str){
    if(str.empty()){//String is empty
        return;
    }

    size_t i,start_pos,end_pos;

    for(i=0;i<str.size();i++){//Get Start Position
        if(!isspace(str[i])){
            break;
        }
    }

    if(i==str.size()){//Only Space and Tabs in string
        return;
    }

    start_pos=i;

    for(i=str.size()-1;i>=0;i--){//Get End Position
        if(!isspace(str[i])){
            break;
        }
    }

    end_pos=i;

    str=str.substr(start_pos,end_pos+1);
}

bool readCfgFile(std::string &cfgfilePath,conf_map &configs){
    //Open The Config File and load config to map
    std::fstream cfgfile;
    cfgfile.open(cfgfilePath);
    if(!cfgfile.is_open()){
        std::cout<<"Failed to open the file!"<<std::endl;
        return false;
    }

    //If Map is not empty,clear it
    if(!configs.empty()){
        configs.clear();
    }

    //Read each line of config file and get value
    char tmp[1000];
    while(!cfgfile.eof()){
        cfgfile.getline(tmp,1000);
        std::string line(tmp),value;
        std::size_t pos = line.find('=');//Get the position of '='

        if(pos == std::string::npos){//No Configs
            continue;
        }

        std::string key=line.substr(0,pos);
        value=line.substr(pos+1);

        //Clear Spaces
        Trim(key);Trim(value);

        configs[key]=value;
    }

    cfgfile.close();
    return true;
}

// Some Test Codes,for Test Purpose only.

// void readcfg(){
//     //Input Config File Path and Key
//     char filename[1000];
//     std::string cfgkey;
//     conf_map test_config;

//     std::cout<<"Input Config File Name:";//Config File Name
//     std::cin.get();//Clear the cin to read line
//     std::cin.getline(filename,1000);

//     std::cout<<"Input Config Key:";//Config Key
//     std::cin>>cfgkey;

//     //Get The Config
//     if(readCfgFile(filename,test_config)){
//         std::cout<<"The Config Of "<<cfgkey<<" is "<<test_config[cfgkey]<<std::endl;
//     }else{
//         std::cout<<"Failed to Read Config!"<<std::endl;
//     }
// }

// void appendcfg(){
//     //Input Config File Path and Key
//     char filename[1000];
//     std::string cfgkey,cfgvalue;

//     std::cout<<"Input Config File Name:";
//     std::cin.get();//Clear the cin to read line
//     std::cin.getline(filename,1000);

//     //Append Config
//     std::fstream cfgfile;
//     cfgfile.open(filename,std::ios_base::app);

//     if(cfgfile.is_open()){
//         std::cout<<"Input Config Key And Config Value:";
//         std::cin>>cfgkey>>cfgvalue;
//         cfgfile<<std::endl;
//         cfgfile<<cfgkey<<"="<<cfgvalue;
//         cfgfile.close();
//     }else{
//         std::cout<<"Config File Open Failed!"<<std::endl;
//     }
// }

// void show_configs(){
//     //Input Config File Path and Key
//     char filename[1000];
//     conf_map test_config;

//     std::cout<<"Input Config File Name"<<std::endl;//Config File Name
//     std::cin.get();//Clear the cin to read line
//     std::cin.getline(filename,1000);

//     //Get The Config and Show all Config in map
//     if(readCfgFile(filename,test_config)){
//         auto mite=test_config.begin();
//         for(;mite!=test_config.end();mite++){
//             std::cout<<mite->first<<"="<<mite->second<<std::endl;
//         }
        
//     }else{
//         std::cout<<"Failed to Read Config!"<<std::endl;
//     }
// }

// int main(int argc,char **argv){
//     //Function Pointer to select mode
//     pfun feature[]={readcfg,appendcfg,show_configs};
//     //Get Selection and execute a mode
//     int selection;
//     std::cout<<"0.Read a Config 1.Append a Config 2.Show all Configs"<<std::endl<<"Selection a mode:";
//     std::cin>>selection;
//     feature[selection]();
//     return 0;
// }
