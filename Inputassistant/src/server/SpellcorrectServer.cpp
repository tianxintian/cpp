 ///
 /// @file    SpellcorrectServer.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-16 21:32:56
 ///
 
#include "SpellcorrectServer.h"
#include "Configuration.h"
#include "net/SocketUtil.h"
#include "cache/CacheManager.h"
#include "timer/TimerThread.h"
#include "Task.h"

#include <iostream>
#include <functional>
using std::cout;
using std::endl;

using namespace hw;

SpellcorrectServer::SpellcorrectServer()
:_threadpool(str2int(Configuration::getInstance()->getConfigMap()[THREAD_NUM]),
			str2int(Configuration::getInstance()->getConfigMap()[TASK_NUM]))
,_tcpServer(Configuration::getInstance()->getConfigMap()[IP],
		str2unshort(Configuration::getInstance()->getConfigMap()[PORT]))
,_isExit(false)
{
	cout<<"SpellcorrectServer()"<<endl;
}


SpellcorrectServer::~SpellcorrectServer()
{
	if(!_isExit)
	{
		stop();
	}
	cout<<"~SpellcorrectServer()"<<endl;
}

void SpellcorrectServer::start()
{
	//初始化cache
	CacheManager::initCache(str2uint(Configuration::getInstance()->getConfigMap()[THREAD_NUM])
			,Configuration::getInstance()->getConfigMap()[CACHE_PATH].c_str());

	//启动线程池
	_threadpool.start();

	//启动定时器
	TimerThread timerThread(2,66,&CacheManager::periodicUpadateCaches);
	timerThread.start();

	//启动server代理
	_tcpServer.setConnectionCallback(std::bind(&SpellcorrectServer::onConnection,this,std::placeholders::_1));
	_tcpServer.setMessageCallback(std::bind(&SpellcorrectServer::onMessage,this,std::placeholders::_1));
	_tcpServer.setCloseCallback(std::bind(&SpellcorrectServer::onClose,this,std::placeholders::_1));
	_tcpServer.start();
}

void SpellcorrectServer::stop()
{
	if(!_isExit)
	{
		_tcpServer.stop();
		_threadpool.stop();
		_isExit=true;
	}
}

void SpellcorrectServer::onConnection(TcpConnectionPtr conn)
{
	cout<<conn->toString()<<endl;
	conn->send("hello,welcome to Spell Correction Server.\n");
}

void SpellcorrectServer::onMessage(TcpConnectionPtr conn)
{
	string query(conn->receive());
	query.pop_back();
	_threadpool.addTask(std::bind(&Task::execute,Task(query,conn)));
}

void SpellcorrectServer::onClose(TcpConnectionPtr conn)
{
	cout<<conn->toString()<<"close"<<endl;
}






