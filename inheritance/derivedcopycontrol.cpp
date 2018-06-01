 ///
 /// @file    derivedcopycontrol.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-01 21:23:03
 ///
 ///派生类与派生类之间的复制控制：
 ///当派生类没有定义复制控制函数(复制构造函数，赋值运算符函数=)
 ///但基类有显式定义复制控制函数，则执行派生类间的复制控制时，会
 ///自动调用基类相应复制控制函数。
#include <iostream>
#include <stdio.h>
#include <string.h>
using std::cout;
using std::endl;

class Base
{
public:
	Base(const char * pdata)
	:_pdata(new char[strlen(pdata)+1]())
	{
		strcpy(_pdata,pdata);
		cout<<"Base(const char *)"<<endl;
	}

	Base(const Base & rhs)
	:_pdata(new char[strlen(rhs._pdata)+1]())
	{
		strcpy(_pdata,rhs._pdata);
		cout<<"Base(const Base &)"<<endl;
	}

	Base & operator=(const Base & rhs)
	{
		cout<<"Base & operator=(const Base &)"<<endl;
		if(this != &rhs)
		{
			delete [] _pdata;
			_pdata = new char[strlen(rhs._pdata)+1]();
			strcpy(_pdata,rhs._pdata);
		}
		return *this;
	}
	
	~Base()
	{
		cout<<"~Base()"<<endl;
		delete [] _pdata;
	}
	friend std::ostream & operator<<(std::ostream & os,const Base &);
private:
	char * _pdata;
};

std::ostream & operator<<(std::ostream & os,const Base & rhs)
{
	os<<rhs._pdata;
	return os;
}

class Derived
:public Base
{
public:
	Derived(const char * pdata)
	:Base(pdata)
	{
		cout<<"Derived(const char *)"<<endl;
	}
	~Derived()
	{
		cout<<"~Derived()"<<endl;
	}
};

int main(void)
{
	Derived d1("hello");
	Derived d2(d1);
	//输出运算符为何可以输出Derived类的对象？
	//因为派生类对象可以适用于基类，匹配基类的operator<<
	cout<<"d1 = "<<d1<<endl;
	cout<<"d2 = "<<d2<<endl;
	cout<<"-----------------------"<<endl;

	Derived d3("world");
	d2=d3;
	cout<<"d2 = "<<d2<<endl;
	cout<<"-----------------------"<<endl;
	return 0;
}
