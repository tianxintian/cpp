 ///
 /// @file    Thread.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-07 19:59:54
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
			_isRunning=false;
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
			pthread->run();//调用派生类实现的虚函数
		return NULL;
	}

	void Thread::join()
	{
		if(_isRunning)
			pthread_join(_pthid,NULL);
	}
}//end of namespace wd


