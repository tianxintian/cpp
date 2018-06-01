 ///
 /// @file    typecast.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-01 22:58:45
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

	Base(int ib)
	:_ib(ib)
	{
		cout<<"Base(int)"<<endl;
	}
	
	void print()const
	{
		cout<<"Base::_ib = "<<_ib<<endl;
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

	Derived(int ib,int id)
	:Base(ib)
	,_id(id)
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
};

int main(void)
{
	//派生类能适应基类
	//意思是派生类的对象能直接用于基类对象
	//所能应用的场合
	//这里也析构了base2，base3
	Base base(10);
	Derived d1(1,2);
	cout<<"sizeof(Base) = "<<sizeof(Base)<<endl;
	cout<<"sizeof(Derived) = "<<sizeof(Derived)<<endl;
	cout<<"-------------------------"<<endl;
	Base base2 = base;//Base(const Base&)
	//把一个派生类对象赋值给基类对象
	Base base3 = d1;//Base(const Base &)
	//Derived d2=base;//error,Derived(const Derived &);
	Base * pbase = &base;
	pbase->print();
	cout<<"-------------------------"<<endl;
	//把一个基类指针指向派生类对象
	pbase = &d1;
	pbase->print();
	cout<<"--------------------------"<<endl;
	//把一个基类引用指向派生类对象
	Base & ref = d1;
	ref.print();
	cout<<"---------------------------"<<endl;
	return 0;
}
