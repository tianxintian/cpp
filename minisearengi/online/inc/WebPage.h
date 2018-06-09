 ///
 /// @file    WebPage.h
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-24 13:13:55
 ///
 
#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__
#include "Configuration.h"
#include "WordSegment.h"

class WebPage
{
public:
	WebPage(){}
	WebPage(string &doc,Configuration &conf,WordSegment &jieba);
	int getDocid(){return _docid;}
	map<string,int>& getwordmap(){return _wordMap;}
	string getDocUrl(){return _docurl;}
	string getDoc(){return _doc;}
	string getDocTitle(){return _doctitle;}
	string summary(const vector<string>& queryword);
private:
	const static int TOPK_NUMBER=10;
	string _doc;
	int _docid;
	string _doctitle;
	string _docurl;
	string _doccontent;
	string _docsummary;
	vector<string> _topword;
	map<string,int> _wordMap;
	friend bool operator ==(const WebPage &lhs,const WebPage & rhs);
	friend bool operator <(const WebPage &lhs,const WebPage &rhs);
	void processDoc(const string &doc,Configuration &conf,WordSegment &jieba);
	void calcTopk(vector<string> &wordsVec,int k,set<string> & stopwordlist);
};

#endif
