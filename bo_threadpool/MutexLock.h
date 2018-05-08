 ///
 /// @file    MutexLock.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 19:22:54
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
}//end of namespace wd

#endif

