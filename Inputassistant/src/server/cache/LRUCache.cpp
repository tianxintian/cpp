 ///
 /// @file    LRUCache.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-15 23:06:51
 ///
 
#include "LRUCache.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::endl;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;
using std::istringstream;

using namespace hw;

//创建一个 lru cache
LRUCache::LRUCache(const size_t & capacity)
:_capacity(capacity)
,_hashMap()
,_lruList()
{
	cout<<"LRUCache()"<<endl;
}

//复制一个 lru cache
LRUCache::LRUCache(const LRUCache & rhs)
:_capacity(rhs._capacity)
{
	update(rhs);
	cout<<"LRUCache(const LRUCache &)";
}

//复制一个 lru cache
LRUCache & LRUCache::operator=(const LRUCache & rhs)
{
	if(this != &rhs)
	{
		_capacity = rhs._capacity;
		update(rhs);
	}
	cout<<"operator=(const LRUCache &)"<<endl;
	return *this;
}

LRUCache::~LRUCache()
{
	cout<<"~LRUCache()"<<endl;
}

//lru  cache 的操作

bool LRUCache::setLRUCache(const string & key,const string & data)
{
	cout<<"setLRUCache()"<<key<<"--->"<<data<<endl;
	//从hash map 里查找关键字
	auto it = _hashMap.find(key);
	if(it!=_hashMap.end())//在_hashMap里找到了
	{
		_hashMap[key]->_data=data;
		updateLRU(key);//更新一下LRU，我查找了
	}else//没找到
	{
		if(_capacity == _lruList.size())
		{
			_hashMap.erase(_lruList.back()._key);
			_lruList.pop_back();
		}
		_lruList.push_front(CacheEntry(key,data));
		_hashMap[key] = _lruList.begin();
	}
	cout<<"setLRUCache() success"<<endl;
	return 0;
}

//从LRU cache里取数据
string LRUCache::getLRUCache(const string & key)
{
	//查找数据
	auto it = _hashMap.find(key);
	if(it != _hashMap.end())//查找到了数据
	{
		updateLRU(key);
		return _hashMap[key]->_data;
	}else//不存在数据
	{
		return "";
	}
}

//输出打印cache列表
void LRUCache::printLRUCache()const
{
	cout<<"\n>>>>>>>>>\n"
		<<"cache:\n"
		<<"key-->data:"<<endl;
	for(auto & entry : _lruList)
	{
		cout<<entry._key<<"-->"<<entry._data<<endl;
	}
	cout<<"\n>>>>>>>>>\n"<<endl;
}

//读数据来初始化cache
void LRUCache::initFromFile(const char * fileName)
{
	ifstream ifs(fileName);
	if(!ifs.good())
	{
		cout<<"ifstream open file failed!"<<endl;
		return;
	}
	string line;
	cout<<"add Cache"<<endl;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		string key;
		//设置的是存储最优的三个结果
		string value1;
		string value2;
		string value3;
		iss>>key>>value1>>value2>>value3;
		string value;
		if(value1 != "")
			value =value1+" "+value2+" "+value3;
		cout<<"key="<<key<<endl
			<<"value="<<value<<endl;
		setLRUCache(key,value);//放入lrucache里
	}
	ifs.close();
}

//把lrucache里的内容输出到文件里
void LRUCache::dumpToFile(const char* fileName)const
{
	ofstream ofs(fileName);
	if(!ofs.good())
	{
		cout<<"ofstream open failed"<<endl;
		return;
	}
	for(auto & entry : _lruList)
	{
		ofs<<entry._key<<" "<<entry._data<<endl;
	}
	ofs.close();
}

//更新整个cache
void LRUCache::update(const LRUCache & rhs)
{
	for(auto & entry : rhs._lruList)
	{
		setLRUCache(entry._key,entry._data);
	}
}

//通过key查找lrucache，返回对应key的元素个数
size_t LRUCache::ishavefound(const string & key)const
{
	return _hashMap.count(key);
}

//更新lrucache其中一个的元素
void LRUCache::updateLRU(const string & key)
{
	//把元素啊放入list头部，然后从list删除以前位置的元素
	_lruList.splice(_lruList.begin(),_lruList,_hashMap[key]);
	_hashMap[key]=_lruList.begin();
}

