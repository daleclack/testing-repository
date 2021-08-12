#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>

typedef std::map<std::string,std::string> conf_map;//Container of configs

bool readCfgFile(std::string &cfgfilePath,conf_map &configs);
