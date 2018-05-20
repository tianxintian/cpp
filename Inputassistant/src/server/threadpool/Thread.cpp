 ///
 /// @file    Thread.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-07 09:54:03
 ///
 
#include "Thread.h"
#include <iostream>
#include <stdio.h>
#include <utility>
using std::cout;
using std::endl;

namespace wd
{
namespace curthread
{//__thread是一个关键字
	__thread const char * threadName = "main";
}//end of namespace curthread

ThreadData::ThreadData(ThreadCallback && cb,const string & name)
:_cb(std::move(cb))
,_name(name)
{}

void ThreadData::runInThread()
{
	curthread::threadName = _name.empty()?"main":_name.c_str();
	::printf("i am thread: %s\n",curthread::threadName);
	if(_cb)
		_cb();
}

Thread::Thread(ThreadCallback && cb,const string & name)
: _pthid(0)
, _isRunning(false)
, _cb(std::move(cb))
,_name(name)
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
	ThreadData * pThreadData = new ThreadData(std::move(_cb),_name);
	pthread_create(&_pthid, NULL, threadFunc, pThreadData);
	_isRunning = true;
}

void * Thread::threadFunc(void * arg)
{
	//这是以前的框架
	//Thread * pthread = static_cast<Thread*>(arg);
	//if(pthread)
	//	pthread->_cb();
	
	ThreadData * pThreadData = static_cast<ThreadData*>(arg);
	if(pThreadData)
		pThreadData->runInThread();
	return NULL;
}

pthread_t Thread::getPthId()
{
	return _pthid;
}

void Thread::join()
{
	if(_isRunning)
		pthread_join(_pthid, NULL);	
		_isRunning=false;
}

}
