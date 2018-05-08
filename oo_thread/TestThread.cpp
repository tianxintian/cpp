 ///
 /// @file    TestThread.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-07 19:03:06
 ///
 
#include "Thread.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class Mythread
:public wd::Thread
{
	public:
		Mythread()
		{
			cout<<"Mythread()"<<endl;
		}
		~Mythread()
		{
			cout<<"~Mythread()"<<endl;
		}
	private:
		void run()
		{
			::srand(time(NULL));
			int cnt = 7;
			while(cnt--)
			{
				int number = rand()%100;
				cout<<"number = "<<number<<endl;
				sleep(1);
			}
		}
};

int main(void)
{
	unique_ptr<wd::Thread> pthread(new Mythread);
	pthread->start();
	pthread->join();
	return 0;
}
