 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 09:54:03
 ///
 
#include "Thread.h"
#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
Thread::Thread(ThreadCallback && cb)
: _pthid(0)
, _isRunning(false)
, _cb(std::move(cb))
{
}

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
	pthread_create(&_pthid, NULL, threadFunc, this);
	_isRunning = true;
}

void * Thread::threadFunc(void * arg)
{
	Thread * pthread = static_cast<Thread*>(arg);
	if(pthread)
		pthread->_cb();

	pthread->_isRunning = false;
	return NULL;
}

void Thread::join()
{
	if(_isRunning)
		pthread_join(_pthid, NULL);	
}

}
