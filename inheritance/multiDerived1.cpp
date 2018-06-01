 ///
 /// @file    multiDerived1.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-01 18:54:54
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
	void display()const
	{
		cout<<"A::display()"<<endl;
	}
};

class B
{
public:
	void display()const
	{
		cout<<"B::display()"<<endl;
	}
};

class C
:public A
,public B
{
public:
	void display()const
	{
		cout<<"C::display()"<<endl;
	}
};


int main(void)
{
	C c;
	//多基派生的二义性:成员名冲突的二义性
	//解决方式为:作用域限定符
	c.A::display();
	c.B::display();
	c.display();
	return 0;
}
