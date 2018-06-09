 ///
 /// @file    Configuration.cpp
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-22 16:18:12
 ///
 
#include "Configuration.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::ofstream;

Configuration::Configuration(const string & filepath)
:_filepath(filepath)
{
	readConfiguration();
}

void Configuration::readConfiguration()
{
	ifstream ifs(_filepath.c_str());
	if(ifs.good())
	{
		string line;
		while(getline(ifs,line))
		{
			istringstream iss(line);
			string key;
			string value;
			iss>>key>>value;
			_configMap[key]=value;
		}
	}else
	{
		cout<<"ifstream open error!"<<endl;
	}
}

map<string,string>& Configuration::getConfigMap()
{
	return _configMap;
}

set<string>& Configuration::getStopWordList()
{
	if(_StopWordList.size()>0)
		return _StopWordList;
	string stopWordFilePath = _configMap["stopword"];
	ifstream ifs(stopWordFilePath.c_str());
	if(!ifs)
	{
		cout<<"StopWord ifstream open error!"<<endl;
	}
	string word;
	while(getline(ifs,word))
	{
		_StopWordList.insert(word);
	}
	return _StopWordList;
}
