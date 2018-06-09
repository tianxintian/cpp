 ///
 /// @file    Wordqueryserver.cpp
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-25 11:10:30
 ///
 

#include "Wordqueryserver.h"
#include "Mylogger.h"
#include <stdlib.h>
#include <stdio.h>
#include <functional>
#include <iostream>
using std::cout;
using std::endl;

Wordqueryserver::Wordqueryserver(Configuration &conf)
:_conf(conf)
,_wqo(_conf)
,_tcpserver(_conf.get_config_map()["ip"].c_str(),
		   atoi(_conf.get_config_map()["port"].c_str()))
,_tpl(4,10)
{
	_tcpserver.setConnectionCallback(std::bind(&Wordqueryserver::onConnection,this,std::placeholders::_1));
	_tcpserver.setMessageCallback(std::bind(&Wordqueryserver::onMessage,this,std::placeholders::_1));
	_tcpserver.setCloseCallback(std::bind(&Wordqueryserver::onClose,this,std::placeholders::_1));
}

void Wordqueryserver::start()
{
	_tpl.start();
	_tcpserver.start();
}

void Wordqueryserver::onConnection(const TcpConnectionPtr & conn)
{
	printf("%s\n",conn->toString().c_str());
}

void Wordqueryserver::onMessage(const TcpConnectionPtr & conn)
{
	string s = conn->receive();
	string data;
	int pos = s.find('\n');
	if(pos>=0)
		data=s.substr(0,pos);
	else
		data=s;
	_tpl.addTask(std::bind(&Wordqueryserver::dotask,this,conn,data));
	//LogDebug("搜索:%s",s.c_str());
}

void Wordqueryserver::onClose(const TcpConnectionPtr & conn)
{
	printf("%s close.\n",conn->toString().c_str());
}

void Wordqueryserver::dotask(const TcpConnectionPtr & conn,const string& data)
{
	string result = _wqo.doQuery(data);
	cout<<"结果:"<<endl;
	cout<<result<<endl;
	conn->sendInLoop(result);
}
	
