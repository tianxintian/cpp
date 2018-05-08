 ///
 /// @file    MutexLock.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 15:38:11
 ///
 
#ifndef __WD_MUTEXLOCK_H__
#define __WD_MUTEXLOCK_H__
#include "Noncopyable.h"
#include <pthread.h>

namespace wd
{
	class MutexLock
	:Noncopyable//这里可写成是默认private的缘故是子类不会访问父类
				//故可以写成默认private的形式
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
	
		class MutexLockGuard//定义这个类是为了防止异常退出没解锁
							//但是这个局部变量的对象销毁的时候会自动
							//调用析构函数，会去解锁
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
