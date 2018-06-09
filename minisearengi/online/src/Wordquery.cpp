 ///
 /// @file    Wordquery.cpp
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-24 15:09:20
 ///
 
#include "Wordquery.h"
#include "Configuration.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <json/json.h>
using std::stable_sort;
using std::endl;
using std::cout;
using std::ifstream;
using std::istringstream;
using std::make_pair;

//余弦相似度比较的结构
//将这个结构体对象放在stable_sort的第三项即可
struct SimilarityCompare
{
	SimilarityCompare(vector<double> & base)
	:_base(base)
	{}
	bool operator()(const pair<int,vector<double>> & lhs,const pair<int,vector<double>> & rhs)
	{
		//每个向量都与基准向量进行计算cos的值
		//按照余弦从大到小排序
		double lhsCrossProduct=0;
		double rhsCrossProduct=0;
		double lhsVectorLength=0;
		double rhsVectorLength=0;
		double basVectorLength=0;

		for(size_t index=0; index != _base.size();++index)
		{
			lhsCrossProduct+=(lhs.second)[index]*_base[index];
			rhsCrossProduct+=(rhs.second)[index]*_base[index];
			lhsVectorLength+=pow((lhs.second)[index],2);
			rhsVectorLength+=pow((rhs.second)[index],2);
			basVectorLength+=pow(_base[index],2);
		}
		if(lhsCrossProduct/(sqrt(lhsVectorLength)*sqrt(basVectorLength))<rhsCrossProduct/(sqrt(rhsVectorLength)*(sqrt(basVectorLength))))
		{
			return false;
		}else
		{
			return true;
		}
	}

	vector<double> _base;
};

Wordquery::Wordquery(Configuration & conf)
:_conf(conf)
{
	loadLibrary();
}

void Wordquery::loadLibrary()
{
	ifstream ifspl(_conf.get_config_map()["newpagelib"]);
	ifstream ifsol(_conf.get_config_map()["newoffsetlib"]);
	if(!ifspl.good()||!ifsol.good())
	{
		cout<<"data lib get fail."<<endl;
	}
	int docid,offset,len;
	string line;
	while(getline(ifsol,line))
	{
		istringstream iss(line);
		iss>>docid>>offset>>len;

		string doc;
		doc.resize(len,' ');//开辟len大小的空间
		ifspl.seekg(offset,ifspl.beg);//定位到第几篇网页
		ifspl.read(&*doc.begin(),len);//读取len个字节到doc里

		WebPage wp(doc,_conf,_jieba);//处理一下这篇网页

		_pagelib.insert(make_pair(docid,wp));
		_offsetlib.insert(make_pair(docid,make_pair(offset,len)));
	}

	ifstream ifsiit(_conf.get_config_map()["invertindexlib"]);
	if(!ifsiit.good())
	{
		cout<<"index table get fail."<<endl;
	}
	string word;
	double weight;
	while(getline(ifsiit,line))
    {
        istringstream iss(line);
        iss>>word;
        set<pair<int,double>> setID;
        while(iss>>docid>>weight)
        {
			setID.insert(make_pair(docid,weight));
        }
        _invertIndexTable.insert(make_pair(word,setID));
    }
	ifspl.close();
	ifsol.close();
	ifsiit.close();
	cout<<"loadLibrary() end."<<endl;
}

string Wordquery::doQuery(const string & strin)
{
	//对输入字符串进行分词
	vector<string> queryword;
	if(strin.size()>0)
	{
		queryword = _jieba(strin.c_str());
	}
	for(auto & item:queryword)
	{
		auto result = _invertIndexTable.find(item);
		if(result == _invertIndexTable.end())
		{
			cout<<"no result "<<item<<endl;
			return returnNoAnswer();
		}
	}

	//计算每个词的权重
	vector<double> weightlist = getQueryWordWeightVector(queryword);
	SimilarityCompare simcmp(weightlist);

	//执行查询,int--docid
	vector<pair<int,vector<double>>> resultVec;
	if(executeQuery(queryword,resultVec))
	{
		stable_sort(resultVec.begin(),resultVec.end(),simcmp);
		vector<int> docIdVec;
		for(auto & item:resultVec)
		{
			docIdVec.push_back(item.first);
		}
		return createJson(docIdVec,queryword);
	}
	return returnNoAnswer();
}

vector<double> Wordquery::getQueryWordWeightVector(vector<string> & queryword)
{
	map<string,int> wordFreqMap;
	for(auto & item:queryword)
	{
		++wordFreqMap[item];
	}
	vector<double> weightlist;
	double weightsum=0;
	int total = _offsetlib.size();
	for(auto & item:queryword)
	{
		int df=_invertIndexTable[item].size();
		double idf = (log(total)-log(df+1))/log(2);
		double weightitem = idf*wordFreqMap[item];
		weightlist.push_back(weightitem);
		weightsum+=pow(weightsum,2);
	}
	for(auto & item:weightlist)
	{
		item /=weightsum;
	}
	return weightlist;
}

bool Wordquery::executeQuery(const vector<string>& queryword,vector<pair<int,vector<double>>> &resultVec)
{
	if(queryword.size()<=0)
	{
		return false;
	}

	int minVec = 1<<20;
	typedef set<pair<int,double>>::iterator setIt;
	vector<pair<setIt,int>> itVec;
	for(auto & item:queryword)
	{
		int crosssize=_invertIndexTable[item].size();
		if(crosssize<minVec)
		{
			minVec=crosssize;
		}
		itVec.push_back(make_pair(_invertIndexTable[item].begin(),0));
	}
	if(minVec==0)
	{
		return false;
	}

	//为了一次遍历就取得结果
	bool isExit = false;
	while(!isExit)
	{
		size_t idx =0;
		for(;idx!=itVec.size()-1;++idx)
		{
			if((itVec[idx].first)->first != (itVec[idx+1].first)->first)
				break;
		}
		if(idx == itVec.size()-1)
		{
			vector<double> weightVec;
			int docid = itVec[0].first->first;
			for(idx=0;idx!=itVec.size();++idx)
			{
				weightVec.push_back(itVec[idx].first->second);
				++(itVec[idx].first);
				++(itVec[idx].second);
				if(itVec[idx].second==minVec)
					isExit=true;
			}
			resultVec.push_back(make_pair(docid,weightVec));
		}
		else
		{
			int itdx=0;
			int minDocid=1<<20;
			for(idx=0;idx!=itVec.size();++idx)
			{
				if(itVec[idx].first->first<minDocid)
				{
					minDocid=itVec[idx].first->first;
					itdx=idx;
				}
			}
			++(itVec[itdx].first);
			++(itVec[itdx].second);
			if(itVec[itdx].second==minVec)
				isExit=true;
		}
	}
	if(resultVec.size()>0)
		return true;
	return false;
}

string Wordquery::createJson(vector<int> & docIdVec,const vector<string> & queryword)
{
	Json::Value root;
	Json::Value arr;
	Json::Value elem;
	int cnt = 0;
	for(auto & id:docIdVec)
	{
		string summary = _pagelib[id].summary(queryword);
		string title = _pagelib[id].getDocTitle();
		string url = _pagelib[id].getDocUrl();
		
		elem["title"] = title;
		elem["summary"] = summary;
		elem["url"] = url;
		arr.append(elem);
		if(++cnt==100)
			break;
	}
	root["files"]=arr;
	Json::StyledWriter writer;
	return writer.write(root);
}

string Wordquery::returnNoAnswer()
{
	Json::Value root;
	Json::Value arr;
	Json::Value elem;
	elem["title"] = "GG";
	elem["summary"]="404 NOT FOUND";
	elem["url"]="";
	arr.append(elem);
	root["files"]=arr;
	Json::StyledWriter writer;
	return writer.write(root);
}



