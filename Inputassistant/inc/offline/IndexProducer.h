 ///
 /// @file    IndexProducer.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-14 14:46:41
 ///
 
#ifndef __MY_INDEXPRODUCER_H__
#define __MY_INDEXPRODUCER_H__

#include <string>
#include <vector>
#include <map>
#include <set>
using std::vector;
using std::set;
using std::map;
using std::pair;
using std::string;

namespace hw
{
	class Configuration;
	class DictProducer;
	class IndexProducer
	{
		public:
			IndexProducer(Configuration&,DictProducer&);//构造函数
			void BuildEnIndex();//建立英文索引
			void BuildCnIndex();//建立中文索引
			void StoreEnIndex();//将英文索引写入文件
			void StoreCnIndex();//将中文索引写入文件
		private:
			Configuration& _config;//配置类引用
			DictProducer& _dict;//字典类引用
			vector<pair<string,int>> _dictvector;//vector字典
			map<string,set<int>> _indexmap;//map的索引
	};
}//end of namespace hw

#endif
