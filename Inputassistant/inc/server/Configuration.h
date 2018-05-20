 ///
 /// @file    Configuration.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-16 14:12:58
 ///
 
#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "Noncopyable.h"
#include <string>
#include <map>
#include <sstream>
using std::string;
using std::map;
using std::istringstream;
using std::ostringstream;
using namespace wd;//这是罗定义的

namespace hw
{
	const char * const CONF_PATH = "./conf/my.conf";
	const char * const DICT_PATH = "mydict";
	const char * const INDEX_PATH = "myindex";
	const char * const THREAD_NUM = "thread_num";
	const char * const TASK_NUM = "task_num";
	const char * const IP = "myip";
	const char * const PORT ="myport";
	const char * const CACHE_PATH = "mycache";
	
	inline string uint2str(const size_t & uint)
	{
		ostringstream oss;
		oss<<uint;
		return oss.str();
	}

	inline std::size_t str2uint(const string & str)
	{
		istringstream iss(str);
		size_t uint;
		iss>>uint;
		return uint;
	}
	
	///获取一个字节高位开头为1的个数
    inline size_t nBytesUTF8Code(const char & ch)
	{
		size_t nBytes=0;
		char chTemp = 1;
		for(size_t idx=0;idx!=6;++idx)
		{
			if(ch & (chTemp <<(7-idx)))
				++nBytes;
			else
				break;
		}
		return nBytes;
	}

	class Configuration
	: Noncopyable
	{
	public:
		static Configuration * getInstance();
		bool init(const char * filepath);
		void display()const;
		map<string,string> & getConfigMap();
	private:
		Configuration();
		~Configuration();
		class AutoRelease
		{
		public:
			AutoRelease();
			~AutoRelease();
		};
	private:
		static Configuration * _pInstance;
		static AutoRelease _autoRelease;
		map<string, string> _configMap;
	};
}//end of namespace hw

#endif
