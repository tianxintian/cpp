 ///
 /// @file    Configuration.h
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-22 16:13:52
 ///
 
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include<set>
#include<map>
#include<string>
using std::map;
using std::set;
using std::string;

class Configuration
{
public:
	Configuration(const string & filepath);
	map<string,string>& getConfigMap();
	set<string>& getStopWordList();
private:
	void readConfiguration();
private:
	string _filepath;
	map<string,string> _configMap;
	set<string> _StopWordList;
};

#endif
