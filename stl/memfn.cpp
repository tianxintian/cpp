 ///
 /// @file    memfn.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-29 21:17:15
 ///
 
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::mem_fn;
struct Foo
{
	void display_greeting()
	{
		cout<<"Hello,world."<<endl;
	}
	void display_number(int i)
	{
		cout<<"number: "<<i<<endl;
	}
	int data = 7;
};

int main()
{
	Foo f;

	auto greet = mem_fn(&Foo::display_greeting);
	greet(f);

	auto print_num= mem_fn(&Foo::display_number);
	print_num(f,42);

	auto access_data = mem_fn(&Foo::data);
	cout<<"data:"<<access_data(f)<<endl;

}
