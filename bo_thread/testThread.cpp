 ///
 /// @file    testThread.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-07 19:31:30
 ///
 
#include "Thread.h"
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <memory>
#include <stdlib.h>
using std::cout;
using std::endl;
using std::unique_ptr;

class Task
{
	public:
		void process()
		{
			srand(time(NULL));
			int cnt = 7;
			while(cnt--)
			{
				int number = rand()%100;
				cout<<"number = "<<number<<endl;
				sleep(1);
			}
		}
};

void getNumber()
{
	srand(time(NULL));
	int cnt = 7;
	while(cnt--)
	{
		int number = rand()%100;
		cout<<"number = "<<number<<endl;
		sleep(1);
	}
}

int main(void)
{
	Task task;
	unique_ptr<wd::Thread> thread(new wd::Thread(std::bind(&Task::process,&task)));
	thread->start();
	thread->join();
	return 0;
}


