 ///
 /// @file    Thread.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 16:22:36
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
			virtual ~Thread();//继承该类的类的析构函数会覆盖
							  //会自动调用这个析构函数

			void start();
			void join();

			bool isRunning()const
			{
				return _isRunning;
			}

		private:
			//函数体内线程池调用的间接函数
			virtual void run()=0;
			//线程执行任务的间接函数
			static void * threadFunc(void * arg);
		private:
			pthread_t _pthid;
			bool _isRunning;
	};
}//end of namespace wd

#endif
