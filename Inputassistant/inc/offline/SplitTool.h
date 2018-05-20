 ///
 /// @file    SplitTool.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-14 00:50:46
 ///
 
#ifndef __MY_SPLITTOOL_H__
#define __MY_SPLITTOOL_H__
#include "Configuration.h"
#include <vector>
using std::vector;

namespace hw
{
	class SplitTool
	{
		public:
			SplitTool(){}
			virtual ~SplitTool(){}
			virtual vector<string> Cut(const string& sentence)=0;//分词函数
	};
	
	class SplitToolCppJieba
	:public SplitTool
	{
		public:
			SplitToolCppJieba(Configuration& conf);
			~SplitToolCppJieba();//覆盖上面那个析构函数。存在虚函数表里面。
			vector<string> Cut(const string& sentence);//分词函数
		private:
			Configuration& _config;
	};
}//end of namespace hw

#endif
