 ///
 /// @file    Wordquery.h
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-24 14:39:59
 ///
 
#ifndef __WORDQUERY_H__
#define __WORDQUERY_H__

#include "WebPage.h"
#include "Configuration.h"
#include "WordSegment.h"
using std::unordered_map;
using std::pair;
using std::set;

class Configuration;
class WebPage;
class Wordquery
{
public:
	Wordquery(Configuration & conf);
	string doQuery(const string & str);//执行查询，返回结果
private:
	Configuration & _conf;//配置文件的引用
	WordSegment _jieba;//Jieba分词库对象
	unordered_map<int,WebPage> _pagelib;//网页库
	unordered_map<int,pair<int,int>> _offsetlib;//偏移库
	unordered_map<string,set<pair<int,double>>> _invertIndexTable;//倒排索引表

	//加载库文件
	void loadLibrary();
	//计算查询词的权重值
	vector<double> getQueryWordWeightVector(vector<string> &);
	//执行查询
	bool executeQuery(const vector<string>&,vector<pair<int,vector<double>>> &);
	//建立json字符串
	string createJson(vector<int> &,const vector<string> &);
	//返回空结果
	string returnNoAnswer();
};

#endif
