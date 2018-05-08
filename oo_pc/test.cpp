 ///
 /// @file    test.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-07 21:25:20
 ///
 
#include "Thread.h"
#include "taskQueue.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

using namespace wd;

class Producer
:public Thread
{
	public:
		Producer(TaskQueue & taskQue)
		:_taskQue(taskQue)
		{}
	private:
		void run()
		{//库里的函数都可以用::调用
			::srand(time(NULL));
			int cnt = 7;
			while(cnt--)
			{
				int number = rand() % 100;
				_taskQue.push(number);
				cout<<">>> producer a number = "<<number<<endl;
				sleep(1);
			}
		}
	private:
		TaskQueue & _taskQue;
};

class Consumer
:public Thread
{
	public:
		Consumer(TaskQueue & taskQue)
		:_taskQue(taskQue)
		{}
	private:
		void run()
		{
			int cnt = 7;
			while(cnt--)
			{
				int number = _taskQue.pop();
				cout<<"> consume a number = "<< number<<endl;
				sleep(2);
			}
		}
	private:
		TaskQueue & _taskQue;
};

int main(void)
{
	TaskQueue taskQueue(10);
	unique_ptr<Thread> producer(new Producer(taskQueue));
	unique_ptr<Thread> consumer(new Consumer(taskQueue));
	producer->start();
	consumer->start();
	producer->join();
	consumer->join();
	return 0;
}


