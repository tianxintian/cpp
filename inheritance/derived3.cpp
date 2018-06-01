 ///
 /// @file    derived3.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-01 20:36:48
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Test
{
public:
	Test()
	{
		cout<<"Test()"<<endl;
	}
	Test(int itest)
	:_itest(itest)
	{
		cout<<"Test(int)"<<endl;
	}
	~Test()
	{
		cout<<"~Test()"<<endl;
	}
private:
	int _itest;
};

class Base
{
public:
	Base()
	{
		cout<<"Base()"<<endl;
	}
	Base(int ib)
	:_ib(ib)
	{
		cout<<"Base(int)"<<endl;
	}
	void print()const
	{
		cout<<"Base::_ib"<<_ib<<endl;
	}
	~Base()
	{
		cout<<"~Base()"<<endl;
	}
private:
	int _ib;
};

class Derived
:public Base
{
public:
	Derived(int id)
	:Base()
	,_id(id)
	{
		cout<<"Derived(int)"<<endl;
	}

	Derived(int ib,int id,int test)
	:Base(ib)//显示调用基类有参构造函数
	,_id(id)
	,_test(test)//对象成员名通过成员名进行构造
	{
		cout<<"Derived(int,int)"<<endl;
	}
	void display()const
	{
		print();
		cout<<"Derived::_id = "<<_id<<endl;
	}

	~Derived()
	{
		cout<<"~Derived()"<<endl;
	}
private:
	int _id;
	Test _test;
};

int main(void)
{
	Derived d(1,2,3);
	d.display();

	return 0;
}

