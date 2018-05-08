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
{
	public:
		Producer()
		{
			cout<<"-------Producer()-------"<<endl;
		}
		void produce(TaskQueue & taskQue)
		{//库里的函数都可以用::调用
			::srand(time(NULL));
			int cnt = 7;
			while(cnt--)
			{
				int number = rand() % 100;
				taskQue.push(number);
				cout<<">>> producer a number = "<<number<<endl;
				sleep(1);
			}
		}
};

class Consumer
{
	public:
		Consumer()
		{
			cout<<"------Consumer()--------"<<endl;
		}
		void consume(TaskQueue & taskQue)
		{
			int cnt = 7;
			while(cnt--)
			{
				int number = taskQue.pop();
				cout<<"> consume a number = "<< number<<endl;
				sleep(2);
			}
		}
};

int main(void)
{
	//传入的都是这个taskQueue的对象，包括10个数量
	TaskQueue taskQueue(10);
	unique_ptr<Thread> producer(
			new Thread(//绑定的函数，临时对象，引用参数
				std::bind(&Producer::produce,
					Producer(),
					std::ref(taskQueue))
			)
	);
	unique_ptr<Thread> consumer(
			new Thread(
				std::bind(&Consumer::consume,
					Consumer(),
					std::ref(taskQueue))
			)
	);
	producer->start();
	consumer->start();
	producer->join();
	consumer->join();
	return 0;
}


