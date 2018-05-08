 ///
 /// @file    Condition.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 19:37:38
 ///
 
#ifndef __WD_CONDITION_H__
#define __WD_CONDITION_H__
#include "Noncopyable.h"
#include <pthread.h>

namespace wd
{
	class MutexLock;//要用这个类，故声明一下。
	class Condition
	:Noncopyable
	{
		public:
			Condition(MutexLock & mutex);
			~Condition();

			void wait();
			void notify();
			void notifyAll();

		private:
			MutexLock & _mutex;
			pthread_cond_t _cond;
	};
}//end of namespace wd

#endif
