 ///
 /// @file    Wordqueryserver.h
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-25 11:03:40
 ///
 
#ifndef __WORDQUERYSERVER_H__
#define __WORDQUERYSERVER_H__
#include "Configuration.h"
#include "Wordquery.h"
#include "TcpServer.h"
#include "Threadpool.h"
using namespace wd;

class Wordqueryserver
{
public:
	Wordqueryserver(Configuration & conf);
	void start();
private:
	Configuration _conf;
	Wordquery _wqo;
	TcpServer _tcpserver;
	Threadpool _tpl;
	void onConnection(const TcpConnectionPtr &conn);
	void onMessage(const TcpConnectionPtr &conn);
	void onClose(const TcpConnectionPtr &conn);
	void dotask(const TcpConnectionPtr &conn, const string &msg);
};

#endif
