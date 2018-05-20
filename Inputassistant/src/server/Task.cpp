 ///
 /// @file    Task.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-16 20:24:28
 ///
 
#include "Task.h"
#include "Configuration.h"
#include "Dictionary.h"
#include "cache/LRUCache.h"
#include "cache/CacheManager.h"
#include "threadpool/Thread.h"
#include "Mylogger.h"
#include "string.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

using namespace hw;
using namespace wd;

//找三个数的最小值
size_t min(const size_t & a,const size_t & b,const size_t & c)
{
	return a<b?(a<c?a:c):(b<c?b:c);
}

//计算最小编辑距离
std::size_t minEditDistance(const std::string & dest, const std::string & src)
{
	std::size_t destSize = dest.size();
	std::size_t srcSize = src.size();

	std::size_t ** pptr = new std::size_t *[destSize + 1]();
	for (std::size_t idx = 0; idx < destSize + 1; ++idx)
	{
		pptr[idx] = new std::size_t[srcSize + 1]();
	}

	//初始化矩阵
	for (std::size_t idx = 0; idx < destSize + 1; ++idx)
	{
		pptr[idx][0] = idx;
	}
	for (std::size_t idx = 1; idx < srcSize + 1; ++idx)
	{
		pptr[0][idx] = idx;
	}

	//构建矩阵，求最小编辑距离
	std::string subDest;
	std::string subSrc;
	for (std::size_t idxDest = 1; idxDest < destSize + 1; ++idxDest)
	{
		std::size_t nBytes = nBytesUTF8Code(dest[idxDest - 1]);
		if (0 == nBytes) { // 处理英文
			subDest = dest.substr(idxDest - 1, 1);
		} else { // 处理中文
			subDest = dest.substr(idxDest - 1, nBytes);
			idxDest += nBytes - 1;
		}

		for (std::size_t idxSrc = 1; idxSrc < srcSize + 1; ++idxSrc)
		{
			nBytes = nBytesUTF8Code(src[idxSrc - 1]);
			if (0 == nBytes) {
				subSrc = src.substr(idxSrc - 1, 1);
			} else {
				subSrc = src.substr(idxSrc - 1, nBytes);
				idxSrc += nBytes - 1;
			}

			if (subDest == subSrc) {
				pptr[idxDest][idxSrc] = pptr[idxDest - 1][idxSrc - 1];
			} else {
				pptr[idxDest][idxSrc] = min(pptr[idxDest - 1][idxSrc] + 1, pptr[idxDest][idxSrc - 1] + 1, pptr[idxDest - 1][idxSrc - 1] + 1);
			}
		}
	}

	std::size_t editDistance = pptr[destSize][srcSize];

	for (std::size_t idx = 0; idx < destSize + 1; ++idx)
	{
		delete [] pptr[idx];
		pptr[idx] = NULL;
	}
	delete [] pptr;
	pptr = NULL;

	return editDistance;
}


Task::Task(const string & query, TcpConnectionPtr conn)
:_query(query)
,_conn(conn)
{
	cout<<"Task()"<<endl;
}

Task::~Task()
{
	cout<<"~Task()"<<endl;
}

//execute计算线程执行的函数
void Task::execute()
{
	//处理业务逻辑
	LogDebug("搜索:%s",_query.c_str());
	LRUCache & lruCache = CacheManager::getCache(str2uint(curthread::threadName));
	if(lruCache.ishavefound(_query)==1)
	{
		cout<<"The result is in the current cache"<<endl;
		string result=lruCache.getLRUCache(_query);
		cout<<"cache result = "<<result<<endl;
		istringstream iss(result);
		string resultTemp;
		while(iss>>result)
		{
			resultTemp += "\n" + result;
		}
		_conn->sendInLoop(resultTemp);
	}else
	{
		cout<<"the result is not in the current cache"<<endl;
		queryIndexTable();//没有在cache里面找到就来索引表找。
		cout<<"query_word = "<<_query<<endl;
		response();//响应客户端请求的函数
	}
}

//cache里面没找到就来这个索引表查找
void Task::queryIndexTable()
{
	unordered_map<string,set<size_t>> & indexTable = Dictionary::getInstance()->getIndexTable();
	size_t nBytes;
	size_t pos=0;
	//hello---> h e l o
	//中文也类似
	set<string> query;
	while(pos != _query.size())
	{
		nBytes = nBytesUTF8Code(_query[pos]);
		if(nBytes == 0)//处理英文
		{
			cout<<_query.substr(pos,1)<<endl;
			query.insert(_query.substr(pos,1));
			++pos;
		}else//处理中文
		{
			cout<<_query.substr(pos,nBytes)<<endl;
			query.insert(_query.substr(pos,nBytes));
			pos += nBytes;
		}
	}
	for(auto & word :query)
	{//预处理，去掉重复
		preprocessing(indexTable[word]);
	}
	//进行计算
	statistic();
}

//预处理，去重，比如hello 在h里有，在e，l，o里面都有
void Task::preprocessing(set<size_t> & iset)
{
	for(auto & idx: iset)
	{
		_queryResult.insert(idx);
	}
}

void Task::statistic()
{
	vector<pair<string,size_t>>& dict =Dictionary::getInstance()->getDict();
	size_t minEditDistance;
	Result result;
    for(auto & idx: _queryResult)
	{
		minEditDistance=calcMinEditDistance(dict[idx].first);
		if(minEditDistance<3)
		{
			result._candidateWord=dict[idx].first;
			result._frequency = dict[idx].second;
			result._minEditDistance=minEditDistance;
			cout<<"resultTemp:"
				<<" "<<result._candidateWord
				<<" "<<result._frequency
				<<" "<<result._minEditDistance<<endl;
			_resultQue.push(result);
		}
	}
}

//计算最小编辑距离
size_t Task::calcMinEditDistance(const string & rhs)
{
	return minEditDistance(_query,rhs);
}

//向客户端进行反馈
void Task::response()
{
	string resultCache;
	if(_resultQue.size()==0)
	{//找不到数据，就不更新cache，取这个名字为了更新cache的
	 //容易引起歧义，因为这并不是在cache里面找的
	 //这边就是直接给客户端发送找不到结果。
		resultCache = "No such result";
		_conn->sendInLoop(resultCache);
	}else
	{
		Result result;
		string resultTemp;
		size_t size = _resultQue.size();
		for(size_t idx=0,count=0;idx!=size;++idx,++count)
		{
			if(count==3)
				break;
			result = _resultQue.top();
			_resultQue.pop();
			//resultTemp用于发送，resultCache用于更新cache
			resultTemp+="\n"+result._candidateWord;
			resultCache+=" "+ result._candidateWord;
		}
		_conn->sendInLoop(resultTemp);
	}
	//对客户端返回的时候同时也更新一下lrucache
	//这边是一个线程名字对应一个lrucache
	LRUCache & lruCache = CacheManager::getCache(str2uint(curthread::threadName));
	lruCache.setLRUCache(_query,resultCache);
}

