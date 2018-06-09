 ///
 /// @file    WebPage.cpp
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-24 13:24:04
 ///
 
#include "WebPage.h"
#include "stdlib.h"
#include <string>
#include <queue>
#include <sstream>
#include <algorithm>
using std::string;
using std::priority_queue;
using std::ifstream;
using std::istringstream;
using std::pair;

struct compare
{
	bool operator()(const pair<string,int> &lhs,const pair<string,int> & rhs)
	{
		if(lhs.second<rhs.second)
		{
			return true;
		}
		else if(lhs.second==rhs.second && lhs.first <rhs.first)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

WebPage::WebPage(string &doc,Configuration &conf, WordSegment &jieba)
:_doc(doc)
{
	_topword.reserve(10);
	processDoc(_doc,conf,jieba);
}

void WebPage::processDoc(const string & doc,Configuration & conf, WordSegment & jieba)
{
	string docidhead="<docid>";
	string docidtail="</docid>";
	string doctihead="<title>";
	string doctitail="</title>";
	string docurlhead="<link>";
	string docurltail="</link>";
	string docconhead="<content>";
	string doccontail="</content>";

	//获取docid
	int sta=doc.find(docidhead);
	int end=doc.find(docidtail);
	string docid = doc.substr(sta+docidhead.size(),end-sta-docidhead.size());
	_docid = atoi(docid.c_str());

	//doctitle
	sta=doc.find(doctihead);
	end=doc.find(doctitail);
	_doctitle=doc.substr(sta+doctihead.size(),end-sta-doctihead.size());

	//doclink
	sta=doc.find(docurlhead);
	end=doc.find(docurltail);
	_docurl=doc.substr(sta+docurlhead.size(),end-sta-docurlhead.size());

	//doccontent
	sta=doc.find(docconhead);
	end=doc.find(doccontail);
	_doccontent=doc.substr(sta+docconhead.size(),end-sta-docurlhead.size());
	
	//其中一篇网页的内容进行分词
	vector<string> s1=jieba(_doccontent.c_str());
	//计算TOPK
	set<string> stopwordlist = conf.get_stopwordlist();
	calcTopk(s1,TOPK_NUMBER,stopwordlist);
}

void WebPage::calcTopk(vector<string> &wordsVec,int k,set<string> &stopwordlist)
{
	for(auto & it:wordsVec)
	{
		auto word = stopwordlist.find(it);
		if(word==stopwordlist.end())
		{
			++_wordMap[it];
		}
	}
	priority_queue<pair<string,int>,vector<pair<string,int>>,compare> p1(_wordMap.begin(),_wordMap.end());
	while(!p1.empty())
	{
		string top = p1.top().first;
		p1.pop();
		if(top.size()==1&&((int)top[0]==10||(int)top[0]==13))
		{
			continue;
		}
		_topword.push_back(top);
		if(_topword.size()>=(size_t)k)
			break;
	}
}

string WebPage::summary(const vector<string>& queryword)
{
	vector<string> summaryvec;
	istringstream iss(_doccontent);
	string line;
	while(iss>>line)
	{
		for(auto & word :queryword)
		{	//如果没找到就返回npos
			if(line.find(word) != string::npos)
			{
				summaryvec.push_back(line);
				break;
			}
		}
		if(summaryvec.size()>=5)
			break;
	}
	string summary;
	for(auto & it: summaryvec)
		summary.append(it).append("\n");
	return summary;
}



bool operator ==(const WebPage &lhs,const WebPage &rhs)
{
	int commNum=0;
	for(auto & it:lhs._topword)
	{
		commNum+=std::count(rhs._topword.begin(),rhs._topword.end(),it);
	}
	int lhsnum=lhs._topword.size();
	int rhsnum=rhs._topword.size();
	int totalnum=lhsnum>rhsnum?lhsnum:rhsnum;
	if((double)(commNum/totalnum)>0.75)
	{
		return 1;
	}
	return 0;
}

bool operator <(const WebPage & lhs,const WebPage & rhs)
{
	return lhs._docid<rhs._docid;
}


