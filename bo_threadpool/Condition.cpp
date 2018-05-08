 ///
 /// @file    Condition.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 19:41:31
 ///
 
#include "Condition.h"
#include "MutexLock.h"

using namespace wd;

Condition::Condition(MutexLock & mutex)
:_mutex(mutex)
{
	pthread_cond_init(&_cond,NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(&_cond);
}

void Condition::wait()
{
	pthread_cond_wait(&_cond,_mutex.getMutexLockPtr());
}

void Condition::notify()
{
	pthread_cond_signal(&_cond);
}

void Condition::notifyAll()
{
	pthread_cond_broadcast(&_cond);
}

