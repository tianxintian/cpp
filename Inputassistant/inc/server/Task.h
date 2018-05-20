 ///
 /// @file    Task.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-16 14:47:18
 ///
 
#ifndef __TASK_H__
#define __TASK_H__

#include "net/TcpConnection.h"
#include <string>
#include <vector>
#include <queue>
#include <set>
using std::string;
using std::vector;
using std::queue;
using std::set;
using std::priority_queue;
using namespace wd;//tcpconn里的
namespace hw
{
	struct Result
	{
		string _candidateWord;
		size_t _frequency;
		size_t _minEditDistance;
	};

	struct Compare
	{
		bool operator()(const Result & lhs,const Result & rhs)
		{
			if(lhs._minEditDistance > rhs._minEditDistance)
			{
				return lhs._minEditDistance>rhs._minEditDistance;
			}else if(lhs._minEditDistance==rhs._minEditDistance
					&& lhs._frequency < rhs._frequency)
			{
				return lhs._frequency < rhs._frequency;
			}else if(lhs._minEditDistance==rhs._minEditDistance
					&& lhs._frequency==rhs._frequency
					&& lhs._candidateWord > rhs._candidateWord)
			{
				return lhs._candidateWord>rhs._candidateWord;
			}else
			{
				return lhs._minEditDistance > rhs._minEditDistance
					&& lhs._frequency < rhs._frequency
					&& lhs._candidateWord > rhs._candidateWord;
			}
		}
	};

	class Task
	{
	public:
		Task(const string & query,TcpConnectionPtr conn);
		~Task();

		//执行查询
		void execute();
	private:
		//查询索引
		void queryIndexTable();
		void preprocessing(set<size_t> & iset);
		//进行计算
		void statistic();
		//计算最小编辑距离
		size_t calcMinEditDistance(const string & rhs);
		//响应客户端的请求
		void response();
	private:
		string _query;
		TcpConnectionPtr _conn;
		set<size_t> _queryResult;
		priority_queue<Result,vector<Result>,Compare> _resultQue;
	};
}//end of namespace hw

#endif

