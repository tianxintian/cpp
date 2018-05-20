 ///
 /// @file    SplitTool.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-14 15:35:00
 ///
 
#include "SplitTool.h"
#include "cppjieba/Jieba.hpp"
#include <iostream>
using std::cout;
using std::endl;
using namespace hw;

SplitToolCppJieba::SplitToolCppJieba(Configuration& conf)
:_config(conf)
{}

SplitToolCppJieba::~SplitToolCppJieba()
{}

vector<string> SplitToolCppJieba::Cut(const string& sentence)
{
	cppjieba::Jieba jieba((_config.GetConfigMap())["dict_path"],
						  (_config.GetConfigMap())["hmm_path"],
						  (_config.GetConfigMap())["user_dict_path"],
						  (_config.GetConfigMap())["idf_path"],
						  (_config.GetConfigMap())["stop_word_path"]);
	vector<string> words;
	jieba.Cut(sentence,words,true);
	return words;
}

//cout<<limon::Join(words.begin(),words.end()," ")<<endl;//这句是打印分词，以空格来分词。
