 ///
 /// @file    Dictionary.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-16 14:34:01
 ///
 
#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include "Noncopyable.h"
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <set>
using std::string;
using std::vector;
using std::unordered_map;
using std::set;
using std::pair;
using namespace wd;

namespace hw
{
	class Dictionary
	:Noncopyable
	{
	public:
		static Dictionary * getInstance();
		void initDict(const char * dictPath);
		void initIndex(const char* indexPath);
		void showDict();
		void showIndexTable();
		
		vector<pair<string,size_t>> & getDict();
		unordered_map<string,set<size_t>> & getIndexTable();
	private:
		Dictionary();
		~Dictionary();
		class AutoRelease
		{
		public:
			AutoRelease();
			~AutoRelease();
		};
	private:
		static Dictionary * _pInstance;
		static AutoRelease _autoRelease;
		vector<pair<string,size_t>> _dict;
		//索引表就是英文字母对应出现这个字母的单词的vector字典下标
		//中文就是一个汉字对应出现这个汉字的词语的vector字典下标
		unordered_map<string,set<size_t>> _indexTable;
	};
}//end of namespace hw

#endif
