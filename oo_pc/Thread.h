 ///
 /// @file    Thread.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-07 19:48:54
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__
#include "Noncopyable.h"
#include <pthread.h>

namespace wd
{
	class Thread
	:Noncopyable
	{
		public:
			Thread();
			virtual ~Thread();

			void start();
			void join();

			bool isRunning()const
			{
				return _isRunning;
			}
		private:
			//线程执行任务函数
			virtual void run()=0;
			//线程的执行体
			static void * threadFunc(void * arg);
		private:
			pthread_t _pthid;
			bool _isRunning;
	};
}//end of namespace wd

#endif
