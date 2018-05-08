 ///
 /// @file    MutexLock.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 19:29:10
 ///
 
#include "MutexLock.h"

using namespace wd;

MutexLock::MutexLock()
:_isLocking(false)
{
	pthread_mutex_init(&_mutex,NULL);
}

MutexLock::~MutexLock()
{
	pthread_mutex_destroy(&_mutex);
}

void MutexLock::lock()
{
	pthread_mutex_lock(&_mutex);
	_isLocking = true;
}

void MutexLock::unlock()
{
	pthread_mutex_unlock(&_mutex);
	_isLocking = false;
}


