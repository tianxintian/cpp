 ///
 /// @file    DictProducer.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-14 15:50:57
 ///
 
#include "DictProducer.h"
#include "Configuration.h"
#include "SplitTool.h"
#include "dirent.h"
#include "stdio.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using namespace hw;


//打开文件的函数
ifstream& OpenFile(ifstream& in,const string& filepath)
{
	in.close();
	in.clear();
	in.open(filepath.c_str());
	return in;
}

void HandleLine(string& line)//处理这一行英文数据的函数
{
	for(size_t num=0;num!=line.size();++num)
	{
		if(!isalpha(line[num]))//去掉标点符号，用空格代替
		{
			line[num]=' ';
		}
		if(isupper(line[num]))
		{
			line[num]^=0x20;//转为小写字母
		}
	}
}

//用于英文的构造函数
//现在定义了但是不调用用
//以防万一有分别生成的时候调用
DictProducer::DictProducer(Configuration& config)
:_diren(config.GetMyEnSources())
,_config(config)
{
	GetFilePath();
}

//把这个原先应用于中文的构造函数改成应用于中英文的构造函数
//多加一个文件路径_filescn
DictProducer::DictProducer(Configuration& config,SplitTool* splittool)
:_diren(config.GetMyEnSources())//用于存储英文的文件路径
,_dircn(config.GetMyCnSources())//用于存储中文的文件路径
,_splittool(splittool)
,_config(config)
{
	GetFilePath();
}

void DictProducer::BuildEnDict()//构建字典，只是放入map里的词频统计
{
	for(auto & elem :_filesen)//读取每一个英文文件的路径,词频统计放入唯一的字典
	{
		ifstream infile;
		if(!OpenFile(infile,elem))
		{
			perror("OpenFile en failure!\n");
		}
		string line;
		string word;
		while(infile>>line)
		{
			HandleLine(line);
			istringstream iss(line);
			while(iss>>word)
			{
				if(_dict.find(word)!=_dict.end())
				{
					++_dict[word];
				}else
				{
					_dict.insert(map<string,int>::value_type(word,1));
				}
			}
		}
		infile.close();
	}
}

//这个可以注释掉，以前用于存储英文字典，现在把中英文存储到一块
//现在是实现了而不调用
void DictProducer::StoreEnDict()//存储字典，输出到字典文件里
{
	ofstream outfile(_config.GetMyEnDict().c_str());
	if(!outfile.good())
	{
		perror("outfile en failure\n");
	}
	for(auto & elem : _dict)
	{
		outfile<<elem.first<<" "<<elem.second<<endl;
	}
	outfile.close();
}

//用唯一的字典对象调用完上面英文字典的建立
//再来调用这个中文字典的建立，在上面的文件上追加
void DictProducer::BuildCnDict()
{
	for(auto & elem :_filescn)//找到每一个文件路径，找到路径就是找到文件
	{
		ifstream infile;
		if(!OpenFile(infile,elem))
		{
			perror("OpenFile cn failure!\n");
		}	
		string line;
		while(getline(infile,line))//读取每一行中文到line里
		{
			vector<string> ret_cut_line;
			ret_cut_line = _splittool->Cut(line);//切割每一行的中文句子，分成每一个单词放入vector<string>
			for(auto & elem: ret_cut_line)
			{
				if(_dict.find(elem)!=_dict.end())
				{
					++_dict[elem];
				}else
				{
					_dict.insert(map<string,int>::value_type(elem,1));
				}
			}
		}
		infile.close();
	}	
}

//存储中文字典
void DictProducer::StoreCnDict()
{
	ofstream outfile(_config.GetMyCnDict().c_str());
	if(!outfile.good())
	{
		perror("outfile cn failure!\n");
	}
	for(auto & elem :_dict)
	{
		outfile<<elem.first<<" "<<elem.second<<endl;
	}
	outfile.close();
}

//调用这个函数，就能通过语料库文件路径
//能够获得所有的语料文件的绝对路径集合
//一次性生成完。
void DictProducer::GetFilePath()
{
	DIR* dir1 =opendir(_diren.c_str());
	if(dir1==NULL)
	{
		perror("opendir failure!\n");
	}
	struct dirent* pdir1;
	char buf[512];//存储文件路径，然后放入vec里保存。
	while((pdir1=readdir(dir1))!=NULL)
	{//忽略.和..文件
		if(!(strcmp(pdir1->d_name,".")==0||strcmp(pdir1->d_name,"..")==0))
		{
			bzero(buf,sizeof(buf));
			sprintf(buf,"%s/%s",_diren.c_str(),pdir1->d_name);
			_filesen.push_back(buf);
		}
	}
	//这里加了个dir2和_dircn来对应中文方面的
	//上面处理的是英文方面的
	DIR* dir2 =opendir(_dircn.c_str());
	if(dir2==NULL)
	{
		perror("opendir failure!\n");
	}
	struct dirent* pdir2;
	char buf2[512];//存储文件路径，然后放入vec里保存。
	while((pdir2=readdir(dir2))!=NULL)
	{//忽略.和..文件
		if(!(strcmp(pdir2->d_name,".")==0||strcmp(pdir2->d_name,"..")==0))
		{
			bzero(buf2,sizeof(buf2));
			sprintf(buf2,"%s/%s",_dircn.c_str(),pdir2->d_name);
			_filescn.push_back(buf2);
		}
	}
}

//查看语料库文件的绝对路径
void DictProducer::ShowFilePath()const
{
	cout<<"显示英文:"<<endl;
	for(auto & elem : _filesen)
	{
		cout<<elem<<endl;
	}
	cout<<"显示中文:"<<endl;
	for(auto & elem1 :_filescn)
	{
		cout<<elem1<<endl;
	}
	cout<<"路径显示完毕"<<endl;
}

//获取字典(map)
map<string,int>& DictProducer::GetDictMap()
{
	return _dict;
}
