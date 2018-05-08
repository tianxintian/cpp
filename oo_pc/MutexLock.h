 ///
 /// @file    MutexLock.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-07 20:29:40
 ///
 
#ifndef __WD_MUTEXLOCK_H__
#define __WD_MUTEXLOCK_H__
#include "Noncopyable.h"
#include <pthread.h>

namespace wd
{
	class MutexLock
	:Noncopyable
	{
		public:
			MutexLock();
			~MutexLock();

			void lock();
			void unlock();
			bool isLocking()const
			{
				return _isLocking;
			}

			pthread_mutex_t * getMutexLockPtr()
			{
				return &_mutex;
			}
		private:
			pthread_mutex_t _mutex;
			bool _isLocking;
	};

	//保护锁，在保护锁里加锁
	//保证不会出现异常，一定能解锁
	//因为会自动调用析构函数
	class MutexLockGuard
	:Noncopyable
	{
		public:
			MutexLockGuard(MutexLock & mutex)
			:_mutex(mutex)
			{
				_mutex.lock();
			}
			~MutexLockGuard()
			{
				_mutex.unlock();
			}
		private:
			MutexLock & _mutex;
	};
}

#endif

