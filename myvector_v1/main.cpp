 ///
 /// @file    main.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-26 19:43:54
 ///
 
#include "vector.h"
#include <iostream>
using std::cout;
using std::endl;

int test()
{
	Vector<int> vecInt;
	display(vecInt);
	cout<<endl;

	vecInt.push_back(1);
	display(vecInt);
	cout<<endl;

	vecInt.push_back(2);
	display(vecInt);
	cout<<endl;

	vecInt.push_back(3);
	display(vecInt);
	cout<<endl;

	vecInt.push_back(4);
	display(vecInt);
	cout<<endl;

	vecInt.push_back(5);
	display(vecInt);
	cout<<endl;

	vecInt.push_back(6);
	display(vecInt);
	cout<<endl;

	vecInt.push_back(7);
	display(vecInt);
	cout<<endl;
	return 0;
}

int main(void)
{
	test();
	return 0;
}

