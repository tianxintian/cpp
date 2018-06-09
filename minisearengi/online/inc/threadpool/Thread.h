 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 09:50:54
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

namespace wd
{

//这是一个具体类
class Thread
: Noncopyable
{
public:
	typedef std::function<void()> ThreadCallback;
	Thread(ThreadCallback && cb);
	~Thread();

	void start();
	void join();

	bool isRunning() const{	return _isRunning;	}

private:
	static void * threadFunc(void * arg);//线程的执行体
private:
	pthread_t _pthid;
	bool _isRunning;
	ThreadCallback _cb;
};

}//end of namespace wd
#endif 



