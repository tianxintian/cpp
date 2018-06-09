 ///
 /// @file    DirScanner.h
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-22 16:40:53
 ///
 
#ifndef DIRSCANNER_H
#define DIRSCANNER_H

#include <string>
#include <vector>
using std::vector;
using std::string;

class Configuration;
const int FileNo=10000;
class DirScanner
{
public:
	DirScanner(Configuration & conf);
	void operator()();
	vector<string> & files();
private:
	void traverse(const string & dirName);
private:
	Configuration & _conf;
	vector<string> _vecFiles;
};

#endif
