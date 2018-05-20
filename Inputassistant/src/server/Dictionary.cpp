 ///
 /// @file    Dictionary.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-16 15:36:46
 ///
 
#include "Dictionary.h"
#include "Configuration.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::string;
using std::istringstream;
using std::ifstream;
using std::ofstream;
using std::make_pair;
using std::cout;
using std::endl;

using namespace hw;

Dictionary * Dictionary::_pInstance = getInstance();
Dictionary::AutoRelease Dictionary::_autoRelease;

Dictionary * Dictionary::getInstance()
{
	if(_pInstance==NULL)
		_pInstance = new Dictionary();
	return _pInstance;
}

//把离线生成的字典文件读入到vector里面
void Dictionary::initDict(const char * dictPath)
{
	ifstream ifs(dictPath);
	if(!ifs.good())
	{
		cout<<"ifstream open file failed!"<<endl;
	}
	string line;
	string word;
	size_t freq;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		iss>>word>>freq;
		_dict.push_back(make_pair(word,freq));
	}
	ifs.close();
	cout<<"-----init dict succeeded---"<<endl;
}

//把离线生成的索引文件读入到_indexTable里面来
void Dictionary::initIndex(const char * indexPath)
{
	ifstream ifs(indexPath);
	if(!ifs.good())
	{
		cout<<"ifstream open file failede!"<<endl;
	}
	string line;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		string key;
		string temp;
		size_t idx;

		//这里修改了试一试
		iss>>key;//>>temp;//这里存了一个：,temp里面
		while(iss>>idx)
		{
			_indexTable[key].insert(idx);
		}
	}
	ifs.close();
	cout<<"init index succeeded"<<endl;
}

//显示在线字典，这个在线字典是从离线生成的字典里读出来的。
//读入到了vector里面，再从vector里面读取出来。
void Dictionary::showDict()
{
	cout<<"Dictionary:"<<endl;
	for(size_t idx = 0; idx != _dict.size();++idx)
	{
		cout<<idx<<" "<<_dict[idx].first<<" "<<_dict[idx].second<<endl;
	}
}

//显示在线索引表
void Dictionary::showIndexTable()
{
	cout<<"show_indextable"<<endl;
	for(auto & elem:_indexTable)
	{
		cout<<elem.first;
		for(auto & idx:elem.second)
		{
			cout<<" "<<idx;
		}
		cout<<endl;
	}
}

//获取字典
vector<pair<string,size_t>> & Dictionary::getDict()
{
	return _dict;
}

//获取索引表
unordered_map<string,set<size_t>> & Dictionary::getIndexTable()
{
	return _indexTable;
}

Dictionary::Dictionary()
{
	cout<<"Dictionary()"<<endl;
}

Dictionary::~Dictionary()
{
	cout<<"~Dictionary()"<<endl;
}

Dictionary::AutoRelease::AutoRelease()
{
	cout<<"Dictionary::AutoRelease()"<<endl;
}

Dictionary::AutoRelease::~AutoRelease()
{
	cout<<"Dictionary::~AutoRelease()"<<endl;
	if(_pInstance)
		delete _pInstance;
}

