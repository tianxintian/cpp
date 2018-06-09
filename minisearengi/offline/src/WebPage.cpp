 ///
 /// @file    WebPage.cpp
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-22 21:20:43
 ///
 
#include "WebPage.h"
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <algorithm>
using std::cout;
using std::endl;
using std::priority_queue;
using std::pair;
using std::make_pair;

struct WordFreqCompare
{
	bool operator()(const pair<string,int>&left,const pair<string,int> &right)
	{
		if(left.second<right.second)
		{
			return true;
		}
		else if(left.second==right.second&&left.first<right.first)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

WebPage::WebPage(string &doc,Configuration &config,WordSegmentation &jieba)
:_doc(doc)
{
	_topWords.reserve(20);
	processDoc(doc,config,jieba);
}

void WebPage::processDoc(const string&doc,Configuration &config,WordSegmentation &jieba)
{
	string docIdHead="<docid>";
	string docIdTail="</docid>";
	string docUrlHead="<link>";
	string docUrlTail="</link>";
	string docTitleHead="<title>";
	string docTitleTail="</title>";
	string docContentHead="<content>";
	string docContentTail="</content>";
	
	//提取文档的docid
	int bpos=doc.find(docIdHead);
	int epos=doc.find(docIdTail);
	string docId=doc.substr(bpos+docIdHead.size(),epos-bpos-docIdHead.size());
	_docId=atoi(docId.c_str());

	//title
	bpos=doc.find(docTitleHead);
	epos=doc.find(docTitleTail);
	_docTitle=doc.substr(bpos+docTitleHead.size(),epos-bpos-docTitleHead.size());

	//content
	bpos=doc.find(docContentHead);
	epos=doc.find(docContentTail);
	_docContent=doc.substr(bpos+docContentHead.size(),epos-bpos-docContentHead.size());

	//利用函数对象调用函数，并分词
	vector<string> wordsVec=jieba(_docContent.c_str());
	set<string> &stopWordList = config.getStopWordList();
	calcTopK(wordsVec,TOPK_NUMBER,stopWordList);
}

void WebPage::calcTopK(vector<string> &wordsVec,int k, set<string> & stopWordList)
{
	for(auto it=wordsVec.begin();it!=wordsVec.end();++it)
	{
		auto sit = stopWordList.find(*it);
		if(sit==stopWordList.end())
		{
			++_wordsMap[*it];
		}
	}
	priority_queue<pair<string,int>,vector<pair<string,int>>,WordFreqCompare>
		wordFreqQue(_wordsMap.begin(),_wordsMap.end());
	while(!wordFreqQue.empty())
	{	//把优先级队列的前k个元素入_topWords
		string top=wordFreqQue.top().first;
		wordFreqQue.pop();
		//这是针对一个特殊的不可见的字符，但统计的时候却一直出现在
		//最高词频中，要剔除掉这个特殊的不可见字符
		if(top.size()==1&&(static_cast<unsigned int>(top[0])==10||static_cast<unsigned int>(top[0])==13))
		{
			continue;
		}
		_topWords.push_back(top);
		if(_topWords.size()>=static_cast<size_t>(k))
		{
			break;
		}
	}
}

bool operator == (const WebPage &lhs,const WebPage &rhs)
{
	int commNum=0;
	auto lit=lhs._topWords.begin();
	for(;lit!=lhs._topWords.end();++lit)
	{
		commNum+=std::count(rhs._topWords.begin(),rhs._topWords.end(),*lit);
	}
	int lhsNum=lhs._topWords.size();
	int rhsNum=rhs._topWords.size();
	int totalNum=lhsNum<rhsNum?lhsNum:rhsNum;
	//大于0.75表明两个网页重合了
	if(static_cast<double>(commNum)/totalNum >0.75)
	{
		return true;
	}else
	{
		return false;
	}
}

bool operator<(const WebPage &lhs,const WebPage &rhs)
{
	if(lhs._docId<rhs._docId)
	{
		return true;
	}else
	{
		return false;
	}
}
