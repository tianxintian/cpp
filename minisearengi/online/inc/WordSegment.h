 ///
 /// @file    WordSegment.h
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-24 13:01:50
 ///
 
#ifndef __WORDSEGMENT_H__
#define __WORDSEGMENT_H__

#include "cppjieba/Jieba.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

const char * const DICT_PATH="./data/JiebaDict/jieba.dict.utf8";
const char * const HMM_PATH="./data/JiebaDict/hmm_model.utf8";
const char * const USER_DICT_PATH="./data/JiebaDict/user.dict.utf8";
const char * const IDF_PATH="./data/JiebaDict/idf.utf8";
const char * const STOP_WORD_PATH="./data/JiebaDict/stop_words.utf8";

class WordSegment
{
public:
	WordSegment()
	:_jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH)
	{}
	vector<string> operator()(const char * src)
	{
		vector<string> words;
		_jieba.Cut(src,words,true);
		return words;
	}
private:
	cppjieba::Jieba _jieba;
};

#endif

