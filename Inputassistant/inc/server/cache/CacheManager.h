 ///
 /// @file    CacheManager.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-15 22:42:16
 ///
 
#ifndef __CACHEMANAGER_H__
#define __CACHEMANAGER_H__

#include <pthread.h>
#include <vector>
#include <map>
using std::vector;
using std::map;

namespace hw
{
	class LRUCache;
	class CacheManager
	{
	public:
		//从磁盘文件读取缓存信息
		static void initCache(const size_t & cacheNum,const char * fileName);
		//获取某个缓存
		static LRUCache & getCache(const size_t & idx);
		//定时更新所有的缓存
		static void periodicUpadateCaches();
	private:
		//缓存的数量与线程的数量是一致的
		static vector<LRUCache> _cacheMap;
		static vector<LRUCache> _cacheMapTemp;
		static char flag;
	};
}//end of namespace hw

#endif
