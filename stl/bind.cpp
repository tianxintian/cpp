 ///
 /// @file    bind.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-26 23:35:14
 ///
 
#include <iostream>
#include <functional>
#include <stdio.h>
using std::cout;
using std::endl;

void print()
{
	cout<<"print()"<<endl;
}

void display()
{
	cout<<"display()"<<endl;
}

void show(int x,int y)
{
	cout<<"show(): x + y = "<<x+y<<endl;
}

int add(int x, int y)
{
	cout<<"int add(int, int)--->x = "<<x<<", y = "<<y<<endl;
	return x+y;
}

struct Example
{
	void show(int x,int y)
	{
		cout<<"Example::show:: x + y = "<<x + y <<endl;
	}

	int add(int x, int y)
	{
		cout<<"int Example::add(int,int)--->x = "<<x<<", y = "<<y<<endl;
		return x + y;
	}
};
//函数指针类型
typedef void(*Function)(void);

void test0(void)
{
	printf("&print = %p\n", print);
	Function f = print;//注册回调函数
	f();//执行回调函数
	f = display;
	f();
	//f=show;//error
}

void test1(void)
{
	auto f0 = print;
	f0();
	cout<<"---------------"<<endl;
	std::function<void()> f = print;//可以把std::function看成函数的容器
	f();
	f=display;
	f();
	cout<<"--------------"<<endl;
	std::function<void(int,int)> f2 =show;
	f2(3,4);
	cout<<"----------------"<<endl;
	auto f1 = std::bind(show,1,2);//void(int,int)---->void(void)
	f1(1,2);
	cout<<"----------------"<<endl;
	f=std::bind(show,1,2);//void(int,int)-------->void(void)
	f();
	cout<<"----------------"<<endl;
	Example ex;
	//绑定成员函数，必须要加上去地址&
	f=std::bind(&Example::show,&ex,10,20);
	f();
}

void test2(void)
{
	//std::bind中绑定参数的位置对应的就是相应函数的形参所在的位置
	//占位符
	std::function<int(int)> f = std::bind(add,std::placeholders::_1,20);
	cout<<f(50)<<endl;
	cout<<"-----------------"<<endl;
	//占位符上的数字代表的是实参传递时的实参位置
	auto f2 = std::bind(add,std::placeholders::_2,20);
	cout<<f2(10,70,80)<<endl;
	cout<<"-----------------"<<endl;
	int number = 11;
	Example ex2;
	//bind绑定参数时采用的是 值传递--->复制
	auto f3 = std::bind(&Example::add,&ex2,std::ref(number),number);
	number = 15;
	cout<<f3()<<endl;
}

int main(void)
{
	//test0();
	//test1();
	test2();
	return 0;
}

