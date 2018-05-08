 ///
 /// @file    Thread.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 16:31:17
 ///
 
#include "Thread.h"

namespace wd
{
	Thread::Thread()
	:_pthid(0)
	,_isRunning(false)
	{}

	Thread::~Thread()
	{
		if(_isRunning)
		{
			pthread_detach(_pthid);
			_isRunning = false;
		}
	}
	
	void Thread::start()
	{
		pthread_create(&_pthid,NULL,threadFunc,this);
		_isRunning = true;
	}

	void * Thread::threadFunc(void * arg)
	{
		Thread * pthread = static_cast<Thread*>(arg);
		if(pthread)
			pthread->run();//多态性之，调用的是workerthread中实现的run函数
						   //那里用threadpool.threadFun()调用了线程池定义的函数
		return NULL;
	}

	void Thread::join()
	{
		if(_isRunning)
			pthread_join(_pthid,NULL);
	}
}
