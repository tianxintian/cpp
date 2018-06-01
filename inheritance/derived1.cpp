 ///
 /// @file    derived1.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-01 19:58:01
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
	Base()
	{
		cout<<"Base()"<<endl;
	}
	void print()const
	{
		cout<<"Base::_ib = "<<_ib<<endl;
	}
private:
	int _ib;
};

class Derived
:public Base
{
public:
	Derived(int id)
	:_id(id)
	{
		cout<<"Derived(int)"<<endl;
	}

	void display()const
	{
		print();
		cout<<"Derived::_id = "<<_id<<endl;
	}

private:
	int _id;
};

int main(void)
{
	//构造派生类对象的时候，会调用默认的基类构造函数
	Derived d(10);
	d.display();
	
	return 0;
}
