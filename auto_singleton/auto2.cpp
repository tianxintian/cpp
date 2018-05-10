 ///
 /// @file    auto2.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-19 19:57:49
 ///
 
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
using std::cout;
using std::endl;

//在linux环境下使用，关联了POSIX的线程库
//atexit + pthread_once

class Singleton
{
public:
	static Singleton * getInstance()
	{
		//在多线程背景下，该函数注册的函数init()
		//只会被执行一次，公用_once指针
		//static注册static类型的
		pthread_once(&_once,init);
		return _pInstance;
	}
	
	static void init()
	{//atexit注册函数注册几次执行几次该函数
		_pInstance = new Singleton;
		::atexit(destroy);
	}

	static void destroy()
	{
		if(_pInstance)
		{
			delete _pInstance;
		}
	}

private:
	Singleton()
	{
		cout<<"Singleton()"<<endl;
	}
	~Singleton()
	{
		cout<<"~Singleton()"<<endl;
	}

	static Singleton * _pInstance;
	static pthread_once_t _once;
};

Singleton * Singleton::_pInstance=NULL;
pthread_once_t Singleton::_once=PTHREAD_ONCE_INIT;

int main(void)
{//用类名::函数名去调用static修饰的成员函数
	Singleton * p1 = Singleton::getInstance();
	Singleton * p2 = Singleton::getInstance();
	cout<<"p1 = "<< p1 <<endl;
	cout<<"p2 = "<< p2 <<endl;

	return 0;
}
