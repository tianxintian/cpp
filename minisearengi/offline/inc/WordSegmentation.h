 ///
 /// @file    WordSegmentation.h
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-22 17:14:52
 ///
 
#ifndef WORDSEGMENTATION_H
#define WORDSEGMENTATION_H

#include "cppjieba/Jieba.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

const char * const DICT_PATH="./data/JiebaDict/jieba.dict.utf8";
const char * const HMM_MODEL_PATH="./data/JiebaDict/hmm_model.utf8";
const char * const USER_DICT_PATH="./data/JiebaDict/user.dict.utf8";
const char * const IDF_PATH="./data/JiebaDict/idf.utf8";
const char * const STOP_WORDS_PATH="./data/JiebaDict/stop_words.utf8";

class WordSegmentation
{
public:
	WordSegmentation()
	:_jieba(DICT_PATH,HMM_MODEL_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORDS_PATH)
	{
		cout<<"cppjieba init!"<<endl;
	}
	vector<string> operator()(const char * src)
	{
		vector<string> words;
		_jieba.CutAll(src,words);
		return words;
	}
private:
	cppjieba::Jieba _jieba;
};

#endif
