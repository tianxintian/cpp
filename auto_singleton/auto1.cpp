 ///
 /// @file    auto1.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-19 19:29:55
 ///
 
#include <iostream>
using std::cout;
using std::endl;
//单例对象自动释放方法一：饱汗模式
//进程创建一个堆空间即可，线程共享

class Singleton
{
	class AutoRelease
	{
		public:
			AutoRelease()
			{
				cout<<"AutoRelease()"<<endl;
			}
			~AutoRelease()
			{
				if(_pInstance)
				{
					cout<<"~AutoRelease()"<<endl;
					delete _pInstance;
				}
			}
	};

public:
	static Singleton* getInstance()
	{
		if(_pInstance == NULL)
		{
			_pInstance = new Singleton;
		}
		return _pInstance;
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

	static Singleton* _pInstance;
	static AutoRelease _auto;
};

//静态成员需要全局初始化；
//静态成员函数需要类名::函数名调用
//这里成员变量和成员函数都是static，故可以省略
Singleton* Singleton::_pInstance=getInstance();
//当线程崩掉了，_auto对象可以自动调用析构函数去释放
Singleton::AutoRelease Singleton::_auto;

int main(void)
{
	Singleton* p1 = Singleton::getInstance();
	Singleton* p2 = Singleton::getInstance();
	cout<<"p1 = "<< p1 << endl;
	cout<<"p2 = "<< p2 << endl;

	return 0;
}
