 ///
 /// @file    Threadpool.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-07 15:28:36
 ///
 
#include "Threadpool.h"
#include "Configuration.h"
#include "Thread.h"
#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;

using namespace wd;
using namespace hw;


Threadpool::Threadpool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskQue(_queSize)
, _isExit(false)
{
	_threads.reserve(_threadNum);
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
	//创建N个子线程对象
	//这个（）里不能动，动了查询就崩溃了
	for(size_t idx = 0; idx != _threadNum; ++idx){
		unique_ptr<Thread> up(new Thread(
			std::bind(&Threadpool::threadFunc, this),uint2str(idx)));
		_threads.push_back(std::move(up));
	}
	//开启N个子线程
	for(auto & thread : _threads)
	{
		thread->start();
	}
}

void Threadpool::stop()
{
	cout << ">>> Threadpool::stop() enter" << endl;
	if(!_isExit){
		while(!_taskQue.empty())
		{
			::sleep(1);
		}
		_isExit = true;

		_taskQue.wakeup();
	}
	for(auto & pthread : _threads)
	{
		pthread->join();
	}
	cout << ">>> Threadpool::stop() exit" << endl;
}

void Threadpool::addTask(Task && task)
{
	_taskQue.push(std::move(task));
}


Threadpool::Task Threadpool::getTask()
{
	return _taskQue.pop();
}

//该方法是每一个子线程要执行的，这是线程取任务执行
void Threadpool::threadFunc()
{
	while(!_isExit)
	{
		Task task = getTask();
		if(task)
			task();
	}
}
