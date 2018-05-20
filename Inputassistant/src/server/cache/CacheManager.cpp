 ///
 /// @file    CacheManager.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-16 00:06:57
 ///
 
#include "CacheManager.h"
#include "Configuration.h"
#include "LRUCache.h"
#include "TimerThread.h"
#include "unistd.h"
#include <iostream>
#include <functional>
using std::cout;

using namespace hw;

vector<LRUCache> CacheManager::_cacheMap;
vector<LRUCache> CacheManager::_cacheMapTemp;
char CacheManager::flag=0;

void CacheManager::initCache(const size_t & cacheNum,const char * fileName)
{
	LRUCache lruCache;
	lruCache.initFromFile(fileName);
	cout<<"---------------\n";
	//预先申请，防止复制
	_cacheMap.reserve(cacheNum);
   for(size_t idx = 0; idx != cacheNum; ++idx)
   {
	   cout<<"init------>cache\n";
	   //初始化每一个lrucache，这里调用复制构造函数
	   _cacheMap.push_back(lruCache);
   }
   cout<<"initCache completed\n";
}

LRUCache & CacheManager::getCache(const size_t & idx)
{//用线程编号对应线程的cache
	return _cacheMap[idx];
}

//第一个for是综合所有的缓存文件写入第一个缓存文件
//再把综合后第一个缓存文件分别写入后续的cache缓存文件
void CacheManager::periodicUpadateCaches()
{
	vector<LRUCache>::iterator it =_cacheMap.begin();
	LRUCache & temp = *it;
	for(++it;it!=_cacheMap.end();++it)
	{
		temp.update(*it);
	}
	it=_cacheMap.begin();
	for(++it;it!=_cacheMap.end();++it)
	{
		(*it).update(temp);
	}
	temp.dumpToFile(Configuration::getInstance()->getConfigMap()[CACHE_PATH].c_str());
	cout<<"periodicUpadateCaches and writeToFile is completed\n";
}

