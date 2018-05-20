 ///
 /// @file    IndexProducer.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-14 19:40:43
 ///
 
#include "Configuration.h"
#include "IndexProducer.h"
#include "DictProducer.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::ofstream;
using namespace hw;

std::size_t nBytesUTF8Code(const char & ch)
{
	std::size_t nBytes = 0;
	char chTemp = 1;
	for(std::size_t idx = 0; idx != 6; ++idx)
	{
		if(ch & (chTemp<<(7 - idx)))
			++nBytes;
		else
			break;
	}
	return nBytes;
}


IndexProducer::IndexProducer(Configuration& config,DictProducer& dict)
:_config(config)
,_dict(dict)
{}

//这个相当于实现了不调用
//因为现在是把中英文索引放在一个文件中
//只调用中文的即可，以后有分别建立索引可以用上
void IndexProducer::BuildEnIndex()
{
	for(auto & elem : _dict.GetDictMap())
	{
		_dictvector.push_back(elem);
	}
	for(std::size_t idx=0; idx!=_dictvector.size();++idx)
	{
		string word = _dictvector[idx].first;
		std::size_t nBytes;
		std::size_t pos = 0;
		while(pos != word.size())
		{
			nBytes = nBytesUTF8Code(word[pos]);
			if(nBytes==0)
			{
				_indexmap[word.substr(pos,1)].insert(idx);
				++pos;
			}else
			{
				_indexmap[word.substr(pos,nBytes)].insert(idx);
				pos+=nBytes;
			}
		}
	}
}

void IndexProducer::BuildCnIndex()
{	//把map的元素转换到vector里面
	for(auto & elem : _dict.GetDictMap())
	{
		_dictvector.push_back(elem);
	}
	for(std::size_t idx=0; idx!=_dictvector.size();++idx)
	{
		string word = _dictvector[idx].first;
		std::size_t nBytes;
		std::size_t pos = 0;
		while(pos != word.size())
		{
			nBytes = nBytesUTF8Code(word[pos]);
			if(nBytes==0)
			{
				_indexmap[word.substr(pos,1)].insert(idx);
				++pos;
			}else
			{
				_indexmap[word.substr(pos,nBytes)].insert(idx);
				pos+=nBytes;
			}
		}
	}
}

//这里也是实现了但是没有调用
void IndexProducer::StoreEnIndex()
{
	ofstream outfile(_config.GetMyEnIndex().c_str());
	if(!outfile.good())
	{
		perror("outfile store failure!\n");
	}
	for(auto & elem: _indexmap)
	{
		outfile<<elem.first<<" ";
		for(auto & set_elem: elem.second)
		{
			outfile<<set_elem<<" ";
		}
		outfile<<endl;
	}
	cout<<"store-En-finish"<<endl;
	outfile.close();
}

//最终调用这个即可，即可生成中英文结合在一块的索引文件
void IndexProducer::StoreCnIndex()
{
	ofstream outfile(_config.GetMyCnIndex().c_str());
	if(!outfile.good())
	{
		perror("outfile store failure!\n");
	}
	for(auto & elem: _indexmap)
	{
		outfile<<elem.first<<" ";
		for(auto & set_elem: elem.second)
		{
			outfile<<set_elem<<" ";
		}
		outfile<<endl;
	}
	cout<<"store-indexfile-finish"<<endl;
	outfile.close();
}


