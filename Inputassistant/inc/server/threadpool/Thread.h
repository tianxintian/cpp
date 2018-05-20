 ///
 /// @file    Thread.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-07 09:50:54
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include "Noncopyable.h"
#include <pthread.h>
#include <functional>
#include <string>
using std::string;

namespace wd
{

namespace curthread
{
	extern __thread const char * threadName;
}//end of namespace curthread

struct ThreadData
{
	typedef std::function<void()> ThreadCallback;
	ThreadData(ThreadCallback && cb, const string & name);
	void runInThread();

	ThreadCallback _cb;
	string _name;
};

//这是一个具体类
class Thread
: Noncopyable
{
public:
	typedef std::function<void()> ThreadCallback;
	Thread(ThreadCallback && cb,const string & name = "");
	~Thread();

	void start();
	void join();

	bool isRunning() const{	return _isRunning;	}

	pthread_t getPthId();
private:
	static void * threadFunc(void * arg);//线程的执行体
private:
	pthread_t _pthid;
	bool _isRunning;
	ThreadCallback _cb;
	string _name;
};

}//end of namespace wd
#endif 



