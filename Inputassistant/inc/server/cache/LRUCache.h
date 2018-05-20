 ///
 /// @file    LRUCache.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-15 22:20:34
 ///
 
#ifndef __LRUCACHE_H__
#define __LRUCACHE_H__

#include <string>
#include <unordered_map>
#include <list>
using std::string;
using std::unordered_map;
using std::list;

namespace hw
{
	//lru的每一个存储单元格式
	struct CacheEntry
	{
		CacheEntry(const string & key,const string & data)
		:_key(key)
		,_data(data)
		{}
		CacheEntry(const CacheEntry & rhs)
		:_key(rhs._key)
		,_data(rhs._data)
		{}
		
		string _key;//数据key
		string _data;//数据data，词频数
	};
    
	//LRU的cache类
	class LRUCache
	{
	public:
		LRUCache(const size_t & capacity = 65536);
		LRUCache(const LRUCache & rhs);
		LRUCache & operator= (const LRUCache & rhs);
		~LRUCache();

		//将数据放入lru缓存里
		bool setLRUCache(const string & key,const string & data);
		//从缓存中取出数据
		string getLRUCache(const string & key);
		//打印缓存中数据
		void printLRUCache()const;
		//从索引文件读入数据到_lrulist
		void initFromFile(const char * fileName);
		//从_lrulist取数据写入本地永久化
		void dumpToFile(const char * fileName)const;
		//更新数据，没读过的插入，读过的就更新list，map
		void update(const LRUCache & rhs);
		//判断有没有查找过这个单词
		size_t ishavefound(const string & key) const;
	
	private:
		void updateLRU(const string & key);
		//cache容量
		size_t _capacity;
		//string就是关键字key，第二项是保存指向key的迭代器
		unordered_map<string,list<CacheEntry>::iterator> _hashMap;
		//保存每一个键值对
		list<CacheEntry> _lruList;
	};
}//end of namespace hw

#endif
