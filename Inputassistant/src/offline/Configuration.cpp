 ///
 /// @file    Configuration.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-15 10:30:05
 ///
 
#include "Configuration.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using namespace hw;

ifstream& openfile(ifstream& in,const string& filepath)
{
	in.close();
	in.clear();
	in.open(filepath.c_str());
	return in;
}

void BuildConfigMap(const string& filepath,map<string,string>& configmap)
{
	ifstream in;
	if(!openfile(in,filepath))
	{
		perror("openfile buildmap failure!\n");
	}
	string config_line;
	while(getline(in,config_line))
	{
		string config_part1,config_part2;
		istringstream iss(config_line);
		iss>>config_part1;
		iss>>config_part2;
		configmap.insert(map<string,string>::value_type(config_part1,config_part2));
	}
}

Configuration::Configuration(const string& filepath)
:_filepath(filepath)
{
	GetConfigMap();
}


map<string,string>& Configuration::GetConfigMap() {
	BuildConfigMap(_filepath,_config_map);
	return _config_map;
}

string& Configuration::GetMyIp() {
	return _config_map["myip"];
}

unsigned short Configuration::GetMyPort() {
	return atoi(_config_map["myport"].c_str());
}

//这里由于修改使得生成唯一的字典文件
//下面四个函数都改成对应一样的
string& Configuration::GetMyEnDict() {
	return _config_map["mydict"];
}

string& Configuration::GetMyCnDict() {
	return _config_map["mydict"];
}

string& Configuration::GetMyEnIndex() {
	return _config_map["myindex"];
}

string& Configuration::GetMyCnIndex() {
	return _config_map["myindex"];
}

string& Configuration::GetMyEnSources() {
	return _config_map["myensources"];
}

string& Configuration::GetMyCnSources() {
	return _config_map["mycnsources"];
}

