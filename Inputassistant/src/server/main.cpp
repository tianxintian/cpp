 // @file    test_server.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-16 22:22:07
 ///
 
#include "Configuration.h"
#include "Dictionary.h"
#include "Mylogger.h"
#include "cache/CacheManager.h"
#include "SpellcorrectServer.h"

#include <iostream>
using std::endl;
using std::cout;
using namespace hw;

int main(void)
{
	LogDebug("启动并使用系统.");
	//这个加载的路径应该是相对于Makefile文件来的
	//这是加载配置文件的路径
	if(!Configuration::getInstance()->init(CONF_PATH))
	{
		cout<<"load Configuration failed."<<endl;
		return -1;
	}
	Configuration::getInstance()->display();

	LogDebug("load dictionary and index.");
	//可以修改这个中英文的文件，切换到自如状态。
	//如果要搜索英文的话
	//这边英文字典文件和索引文件分别对应DICT_EN_PATH和INDEX_EN_PATH
	//将下面两行代码中方括号内容写成DICT_EN_PATH和INDEX_EN_PATH
	//如果要搜索中文的话
	//这边中文字典文件和索引文件分别对应DICT_CH_PATH和INDEX_CH_PATH
	//将下面两行代码中方括号内容写成DICT_CH_PATH和INDEX_CH_PATH
	//等会测试放一起行不行,上面备注先不改，我在这里测试放一起读入
	//这样一起读入的话尝试不行，还要做修改
	//已经修改好了，所以现在可以直接调用
//	Dictionary::getInstance()->initDict(Configuration::getInstance()->getConfigMap()[DICT_EN_PATH].c_str());
	Dictionary::getInstance()->initDict(Configuration::getInstance()->getConfigMap()[DICT_PATH].c_str());
//	Dictionary::getInstance()->initIndex(Configuration::getInstance()->getConfigMap()[INDEX_EN_PATH].c_str());
	Dictionary::getInstance()->initIndex(Configuration::getInstance()->getConfigMap()[INDEX_PATH].c_str());
	Dictionary::getInstance()->showDict();//可以不显示
	Dictionary::getInstance()->showIndexTable();//也可以不显示

	//启动服务
	SpellcorrectServer server;
	server.start();
	
	return 0;
}

