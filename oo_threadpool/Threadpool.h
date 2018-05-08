 //
 /// @file    Threadpool.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 16:45:34
 ///
 
#ifndef __WD_THREADPOOL_H__
#define __WD_THREADPOOL_H__
#include "TaskQueue.h"
#include <vector>
#include <memory>
using std::unique_ptr;
using std::vector;

namespace wd
{
	class Task
	{
		public:
			virtual
			void process()=0;//给mytask去实现这个方法。
	};

	//这里要用到这两个类
	class Thread;
	class WorkerThread;
	class Threadpool
	{
		friend WorkerThread;
		public:
			Threadpool(size_t threadNum,size_t queSize);
			~Threadpool();

			void start();//启动线程池
			void stop();//关闭线程池
			void addTask(Task *);//添加任务到任务队列
		private:
			Task * getTask();//线程池自己取任务指针
			void threadFunc();//线程池要干嘛的函数
		private:
			size_t _threadNum;
			size_t _queSize;
			vector<unique_ptr<Thread>> _threads;
			TaskQueue _taskQue;
			bool _isExit;//表示线程池是否退出
	};
}//end of namespace wd

#endif
