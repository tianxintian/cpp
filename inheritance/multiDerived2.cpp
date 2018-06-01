 ///
 /// @file    multiDerived2.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-01 19:21:35
 ///
 ///采用虚继承以后，整个继承中只有一个A
#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
	void display()const
	{
		cout<<"A::display() _ia = "<<_ia<<endl;
	}
	void setA(int ia)
	{
		_ia=ia;
	}
private:
	int _ia;
};

class B
:virtual public A
{
public:
	void show()const
	{
		cout<<"B::show()"<<endl;
	}
};

class C
:virtual public A
{
public:
	void show()const
	{
		cout<<"C::show()"<<endl;
	}
};

class D
:public B
//逗号前面要加关键字，默认是private继承
,public C
{};

int main(void)
{
	//多基派生的二义性:存储的二义性-->采用虚继承
	D d;
	d.setA(10);
	d.display();
	return 0;
}
