 ///
 /// @file    PageLib.h
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-22 19:18:31
 ///
 
#ifndef PAGELIB_H
#define PAGELIB_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class Configuration;
class DirScanner;
class PageLib
{
public:
	PageLib(Configuration &conf,DirScanner &dirScanner);
	void create();
	void store();
private:
	Configuration & _conf;
	DirScanner &_dirScanner;
	vector<string> _vecPages;
};

#endif
