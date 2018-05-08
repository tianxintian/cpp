 ///
 /// @file    WorkerThread.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 16:37:54
 ///
 
#ifndef __WD_WORKERTHREAD_H__
#define __WD_WORKERTHREAD_H__
#include "Thread.h"
#include "Threadpool.h"
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{
	class WorkerThread
	:public Thread
	{
		public:
			WorkerThread(Threadpool & threadpool)//下面用对象去调用才是用
			:_threadpool(threadpool)			 //线程池对象去初始化的原因
			{
				cout<<"WorkerThread()"<<endl;
			}
			~WorkerThread()
			{
				cout<<"~WorkerThread()"<<endl;
			}
		private:
			void run()//这里是继承Thread的原因，为了实现run函数
			{		  //每一个线程应该干什么
				_threadpool.threadFunc();//这里是去调用定制的函数
			}							 //真正的是每个线程要去干嘛
			Threadpool & _threadpool;//这是线程池的对象，因为上面一行在调用
	};
}//end of namespace wd

#endif
