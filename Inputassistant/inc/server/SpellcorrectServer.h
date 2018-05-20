 ///
 /// @file    SpellcorrectServer.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-16 15:09:47
 ///
 

#ifndef __SPELLCORRECTSERVER_H__
#define __SPELLCORRECTSERVER_H__

#include "net/TcpServer.h"
#include "threadpool/Threadpool.h"
using namespace wd;

namespace hw
{
	class SpellcorrectServer
	{
	public:
		SpellcorrectServer();
		~SpellcorrectServer();
		void start();
		void stop();

	private:
		void onConnection(TcpConnectionPtr conn);
		void onMessage(TcpConnectionPtr conn);
		void onClose(TcpConnectionPtr conn);
	private:
		Threadpool _threadpool;
		TcpServer _tcpServer;
		bool _isExit;
	};
}//end of namespace hw

#endif
