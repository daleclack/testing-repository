#pragma once

#include <iostream>
#include <fstream>
#include <string>

bool readCfgFile(const char * cfgfilePath,const std::string &key,std::string &value);
