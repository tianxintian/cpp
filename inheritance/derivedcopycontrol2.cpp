 ///
 /// @file    derivedcopycontrol2.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-01 21:51:26
 ///
 ///当派生类没有定义复制控制函数的时候，但基类有显式定义复制控制函数
 ///则执行派生类间的复制控制的时候，会自动调用基类相应复制控制函数
 ///
 ///当派生类有显式定义复制控制函数时，基类也有显式定义复制控制函数
 ///则执行派生类间的复制控制时，不会再自动调用基类相应复制控制函数
 ///这时候必须手动显式调用基类的复制控制函数。(在执行派生类复制控制函数的时候)
#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Base
{
public:
	Base()
	:_pdata(new char[1]())
	{
		cout<<"Base()"<<endl;
	}

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
		cout<<"Base & operator =(const Base &)"<<endl;
		if(this != &rhs)
		{
			delete [] _pdata;
			_pdata=new char[strlen(rhs._pdata)+1]();
			strcpy(_pdata,rhs._pdata);
		}
		return *this;
	}

	~Base()
	{
		cout<<"~Base()"<<endl;
		delete [] _pdata;
	}

	friend std::ostream & operator<<(std::ostream & os,const Base & rhs);
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
	Derived(const char *pdata,const char * pdata2)
	:Base(pdata)//显式调用基类构造函数
	,_pdata2(new char[strlen(pdata2)+1]())
	{
		strcpy(_pdata2,pdata2);
		cout<<"Derived(const char *,const char *)"<<endl;
	}
	
	Derived(const Derived & rhs)
	:Base(rhs)//显式调用基类构造函数
	,_pdata2(new char[strlen(rhs._pdata2)+1]())
	{
		strcpy(_pdata2,rhs._pdata2);
		cout<<"Derived(const Derived &)"<<endl;
	}

	Derived & operator=(const Derived & rhs)
	{
		cout<<"Derived & operator=(const Derived & rhs)"<<endl;
		if(this != & rhs)
		{
			//显式调用基类赋值运算符函数
			Base::operator=(rhs);
			delete [] _pdata2;
			_pdata2 = new char[strlen(rhs._pdata2)+1]();
			strcpy(_pdata2,rhs._pdata2);
		}
		return *this;
	}

	~Derived()
	{
		cout<<"~Derived()"<<endl;
		delete [] _pdata2;
	}

	friend std::ostream & operator<<(std::ostream & os,const Derived & rhs);
private:
	char * _pdata2;
};

std::ostream & operator<<(std::ostream & os,const Derived & rhs)
{//这里派生类适应于基类，有类型转换rhs。
	os<<(Base &)rhs<<" "
	  <<rhs._pdata2;
	return os;
}

int main(void)
{
	Derived d1("hello","world");
	cout<<"d1 = "<<d1<<endl;
	cout<<"---------------------"<<endl;

	Derived d2(d1);
	cout<<"d2 = "<<d2<<endl;
	cout<<"---------------------"<<endl;

	Derived d3("wangdao","shenzhen");
	cout<<"d3 = "<<d3<<endl;
	d2=d3;
	cout<<"d2 = "<<d2<<endl;
	cout<<"---------------------"<<endl;
}



