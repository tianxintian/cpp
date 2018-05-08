 ///
 /// @file    TaskQueue.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 16:04:56
 ///
 
#ifndef __WD_TASKQUEUE_H__
#define __WD_TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>

namespace wd
{
	class Task;
	class TaskQueue
	{
		public:
			using Type = Task *;
			TaskQueue(int queSize);

			bool full() const;
			bool empty() const;

			void push(Type & type);
			Type pop();
			void wakeup();//防止退出不了添加的wakeup唤醒所有函数的方法
		private:
			size_t _queSize;
			std::queue<Type> _que;
			MutexLock _mutex;
			Condition _notFull;
			Condition _notEmpty;
			bool _flag;//设置是为了在pop那个wait的地方退出的
	};
}

#endif
