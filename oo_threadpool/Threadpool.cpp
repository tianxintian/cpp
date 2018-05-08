 ///
 /// @file    Threadpool.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 16:55:08
 ///
 
#include "Threadpool.h"
#include "WorkerThread.h"
#include <unistd.h>

using namespace wd;

Threadpool::Threadpool(size_t threadNum,size_t queSize)
:_threadNum(threadNum)
,_queSize(queSize)
,_taskQue(_queSize)
,_isExit(false)
{
	_threads.reserve(threadNum);//分配多少个存储空间
}

Threadpool::~Threadpool()
{
	if(!_isExit)
	{
		stop();
	}
}

void Threadpool::start()
{
	//创建子线程对象
	for(size_t idx = 0; idx != _threadNum; ++idx)
	{//这个this是线程池指针，供给workerthread的类去调用线程该干嘛
	 //用基类指针去指向这个派生类的对象
		unique_ptr<Thread> up(new WorkerThread(*this));
		_threads.push_back(std::move(up));
	}
	//开启子线程
	for(auto & thread : _threads)
		thread->start();//这个start是从thread里继承来的
}

void Threadpool::stop()
{
	if(!_isExit)
	{
		while(!_taskQue.empty())
		{//若任务队列不空一直等线程取完任务执行完
			::sleep(1);
		}
	    _isExit = true;
		_taskQue.wakeup();
	}
	for(auto & pthread : _threads)
	{
		pthread->join();
	}
}

void Threadpool::addTask(Task * ptask)
{
	_taskQue.push(ptask);
}

Task * Threadpool::getTask()
{
	return _taskQue.pop();
}

//线程应该干什么的函数
void Threadpool::threadFunc()
{
	while(!_isExit)
	{
		Task * ptask = getTask();
		if(ptask)
			ptask->process();//执行对应的实现函数
	}
}
