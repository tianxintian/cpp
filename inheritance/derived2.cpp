 ///
 /// @file    derived2.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-01 20:06:08
 ///
 ///当派生类没有显示定义构造函数的时候，而基类有
 ///则基类必须拥有默认构造函数
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
	Base(int ib)
	:_ib(ib)
	{
		cout<<"Base(int)"<<endl;
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
	Derived d;
	d.display();
	return 0;
}
