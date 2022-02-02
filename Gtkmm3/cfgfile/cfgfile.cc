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

bool readCfgFile(const char * cfgfilePath,const std::string &key,std::string &value){
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
            continue;
        }

        std::string tmpkey=line.substr(0,pos);
        if(tmpkey == key){
            value=line.substr(pos+1);
            Trim(value);
            cfgfile.close();
            return true;
        }
    }

    cfgfile.close();
    return false;
}
