 ///
 /// @file    DirScanner.cpp
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-22 16:47:56
 ///
 
#include "DirScanner.h"
#include "Configuration.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
using std::cout;
using std::endl;

DirScanner::DirScanner(Configuration & conf)
:_conf(conf)
{
	_vecFiles.reserve(FileNo);
}

void DirScanner::operator()()
{
	map<string,string>& configMap=_conf.getConfigMap();
	string dirName = configMap["yuliao"];
	traverse(dirName);
}

vector<string> & DirScanner::files()
{
	return _vecFiles;
}

void DirScanner::traverse(const string & dirName)
{
	DIR *dp;
	cout<<"dirName:"<<dirName<<endl;
	if((dp=opendir(dirName.c_str()))==NULL)
	{
		perror("opendir error!");
		exit(-1);
	}
    struct dirent * pdirent;
	char buf[128]={0};
	while((pdirent=readdir(dp))!=NULL)
	{
		if(pdirent->d_type==4)
		{
			if(strcmp(pdirent->d_name,".")==0||strcmp(pdirent->d_name,"..")==0)
			{
				continue;
			}else
			{
				bzero(buf,sizeof(buf));
				sprintf(buf,"%s%c%s",dirName.c_str(),'/',pdirent->d_name);
				traverse(buf);
			}
		}else
		{
			string filename="";
			filename=filename+dirName.c_str();
			filename=filename+"/"+pdirent->d_name;
			_vecFiles.push_back(filename);
		}
	}
}

