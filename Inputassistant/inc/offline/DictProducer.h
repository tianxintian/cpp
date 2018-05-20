 ///
 /// @file    DictProducer.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-14 14:27:05
 ///

//#ifndef __MY_DICTPRODUCER_H__
//#define __MY_DICTPRODUCER_H__

#include <string>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::map;

namespace hw
{
	class Configuration;
	class SplitTool;
	class DictProducer
	{
		public:
			DictProducer(Configuration& config);//构造函数,以前是用于中文处理
			//把下面这个以前用于英文的构造函数，改成中英文可以共同使用的
			DictProducer(Configuration& config,SplitTool* split_tool);//中英文处理
			void BuildEnDict();//创建英文字典
			void BuildCnDict();//创建中文字典
			void StoreEnDict();//将英文字典写入文件
			void StoreCnDict();//将中文字典写入文件
			void ShowFilePath() const;//查看文件路径，作为测试用
			void GetFilePath();//获取文件的绝对路径
			void PushDict(const string & word);//存储某个单词，貌似没用
			map<string,int>& GetDictMap();//获取字典的map
		private:
			string _diren;//语料库英文文件存放路径
			string _dircn;//语料库中文文件存放路径
			vector<string> _filesen;//语料库英文文件的绝对路径集合
			vector<string> _filescn;//语料库中文文件的绝对路径集合
			map<string,int> _dict;//字典内容,就是词频统计，中英合用的唯一字典对象
			SplitTool* _splittool;//分词工具，使用指针的目的是可以以空指针存在，在只用英文字典时可以不初始化
			Configuration& _config;//配置类的引用
	};
}//end of namespace hw

//#endif
