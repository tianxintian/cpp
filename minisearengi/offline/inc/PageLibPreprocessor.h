 ///
 /// @file    PageLibPreprocessor.h
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-22 22:47:50
 ///
 
#ifndef PAGELIBPREPROCESSOR_H
#define PAGELIBPREPROCESSOR_H

#include "WebPage.h"
#include "WordSegmentation.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::map;
using std::unordered_map;
using std::set;

class PageLibPreprocessor
{
public:
	PageLibPreprocessor(Configuration &conf);
	void doProcess();
private:
	void readInfoFromFile();
	void cutRedundantPages();
	void buildInvertIndexTable();
	void storeOnDisk();
private:
	Configuration & _conf;
	WordSegmentation _jieba;
	vector<WebPage> _pageLib;
	unordered_map<int,pair<int,int>> _offsetLib;
	unordered_map<string,vector<pair<int,double>>> _invertIndexTable;
};

#endif
