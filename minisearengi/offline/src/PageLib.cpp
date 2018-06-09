 ///
 /// @file    PageLib.cpp
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-22 19:22:20
 ///
 
#include "Configuration.h"
#include "PageLib.h"
#include "DirScanner.h"
#include "RssReader.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::vector;

PageLib::PageLib(Configuration &conf,DirScanner &dirScanner)
:_conf(conf)
,_dirScanner(dirScanner)
{}

//创建网页库，把每一篇网页写成string放入vector<string>内。
void PageLib::create()
{
	vector<string> &vecFiles = _dirScanner.files();
	RssReader reader(vecFiles);
	reader.loadFeedFiles();
	reader.makePages(_vecPages);
}

void PageLib::store()
{
	map<string,string> &confMap=_conf.getConfigMap();
	string pageLibPath = confMap["ripepagelib"];
	string offsetLibPath = confMap["offsetlib"];
	ofstream ofsPage(pageLibPath.c_str());
	ofstream ofsOffset(offsetLibPath.c_str());
	if(!(ofsPage.good() && ofsOffset.good()))
	{
		cout<<"ofstream open error!"<<endl;
		return;
	}
	for(size_t idx=0;idx!=_vecPages.size();++idx)
	{
		int id=idx+1;
		int length=_vecPages[idx].size();
		ofstream::pos_type offset = ofsPage.tellp();
		ofsPage<<_vecPages[idx];
		ofsOffset<<id<<'\t'<<offset<<'\t'<<length<<'\n';
	}
	ofsPage.close();
	ofsOffset.close();
}
