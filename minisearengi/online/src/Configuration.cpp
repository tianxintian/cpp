 ///
 /// @file    Configuration.cpp
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-24 00:00:54
 ///
 
#include "Configuration.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::ifstream;
using std::istringstream;

Configuration::Configuration(const string & filepath)
:_confpath(filepath)
{
	ifstream ifs(_confpath);
	string line;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		string key,value;
		iss>>key>>value;
		_confmap[key]=value;
	}
	ifs.close();
}

map<string,string>& Configuration::get_config_map()
{
	return _confmap;
}

set<string> Configuration::get_stopwordlist()
{
	ifstream ifs(_confmap["stopword"]);
	string word;
	while(ifs>>word)
	{
		_stopwordlist.insert(word);
	}
	ifs.close();
	_stopwordlist.insert(" ");
	return _stopwordlist;
}



