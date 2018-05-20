 ///
 /// @file    Configuration.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-16 15:23:54
 ///
 
#include "Configuration.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;
using std::string;
using std::make_pair;

using namespace hw;

Configuration * Configuration::_pInstance = getInstance();
Configuration::AutoRelease Configuration::_autoRelease;

Configuration * Configuration::getInstance()
{
	if(_pInstance == NULL)
		_pInstance = new Configuration();
	return _pInstance;
}

//读配置文件，并初始化到配置map里面去。
bool Configuration::init(const char * filePath)
{
	ifstream ifs(filePath);
	if(!ifs.good())
	{
		cout<<"ifstream open file failed!"<<endl;
		return false;
	}
	string line;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		string key;
		string value;
		iss>>key>>value;
		_configMap.insert(make_pair(key,value));
	}
	ifs.close();
	return true;
}

//显示配置文件
void Configuration::display()const
{
	cout<<"Configuration file"<<endl;
	for(auto map: _configMap)
	{
		cout<<map.first<<"--->"<<map.second<<endl;
	}
}

//获取配置map
map<string,string> & Configuration::getConfigMap()
{
	return _configMap;
}

Configuration::Configuration()
{
	cout<<"Configuration()"<<endl;
}

Configuration::~Configuration()
{
	cout<<"~Configuration()"<<endl;
}

//虽然AutoRelease是私有的但是也可以这么来使用。
Configuration::AutoRelease::AutoRelease()
{
	cout<<"Configuration::AutoRelease()"<<endl;
}

Configuration::AutoRelease::~AutoRelease()
{
	cout<<"Configuration::~AutoRelease()"<<endl;
	if(_pInstance)
		delete _pInstance;
}

