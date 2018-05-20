 ///
 /// @file    Configuration.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-14 00:19:35
 ///
 
#ifndef __MY_CONFIGURATION_H__
#define __MY_CONFIGURATION_H__
#include <iostream>
#include <map>
using std::string;
using std::map;

namespace hw
{
	class Configuration
	{
		public:
			Configuration(const string& filepath);//构造函数
			map<string,string>& GetConfigMap();//获取存放配置文件内容的map
			string& GetMyIp();//获取ip
			unsigned short GetMyPort();//获取端口号
			string& GetMyEnDict();//得到英文字典
			string&	GetMyCnDict();//得到中文字典
			string& GetMyEnIndex();//得到英文索引
			string& GetMyCnIndex();//得到中文索引
			string& GetMyEnSources();//获取英文文件
			string& GetMyCnSources();//获取中文文件
		private:
			string _filepath;//文件路径
			map<string, string> _config_map;//配置文件内容的map
	};
}//end of namespace hw

#endif
