 ///
 /// @file    test.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 17:12:07
 ///
 
#include "Threadpool.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using std::cout;
using std::endl;
using namespace wd;

class MyTask
:public Task
{
	public:
		void process()
		{
			::srand(::clock());
			int number = ::rand()%100;
			cout<<">>> produce a number = "<<number<<endl;
		}
};

int main()
{
	Threadpool threadpool(4,10);
	threadpool.start();
	unique_ptr<Task> ptask(new MyTask());
	int cnt = 20;
	while(cnt--)
	{
		cout<<">>>cnt = "<<cnt<<endl;
		threadpool.addTask(ptask.get());//通过线程池对象将任务指针添加进任务队列
	}
	threadpool.stop();
	return 0;
}


