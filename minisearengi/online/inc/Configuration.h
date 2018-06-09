 ///
 /// @file    Configuration.h
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-23 23:52:14
 ///
 
#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <map>
#include <set>
#include <string>
using std::map;
using std::set;
using std::string;

class Configuration
{
public:
	Configuration(const string&);
	map<string,string> &get_config_map();
	set<string> get_stopwordlist();
private:
	string _confpath;
	map<string,string> _confmap;
	set<string> _stopwordlist;
};

#endif


