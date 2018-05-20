 ///
 /// @file    test4_jieba.cc
 /// @author  chenchao(anqing_chao@163.com)
 /// @date    2016-05-24 15:44:36
 ///
 
#include "Configuration.h"
#include "DictProducer.h"
#include "IndexProducer.h"
#include "SplitTool.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace hw;

int main() {
Configuration config("./conf/my.conf");
	SplitToolCppJieba* p_jieba=new SplitToolCppJieba(config);
	DictProducer dict_(config,p_jieba);
	dict_.ShowFilePath();
	dict_.BuildEnDict();
	dict_.BuildCnDict();
	dict_.StoreCnDict();//最终生成的中英文结合在一块的字典
	IndexProducer index_(config,dict_);
	index_.BuildCnIndex();//最后把中英文索引一起建立的
	index_.StoreCnIndex();//存储索引文件
}
