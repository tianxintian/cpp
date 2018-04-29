 ///
 /// @file    for_each.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-27 10:25:40
 ///
 /// for_each,replace,replace_if
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::for_each;

void print(int number)
{
	cout<<number<<" ";
}

void test1(void)
{
	int a = 10;
	int b = 100;
	vector<int> numbers{1,2,3,4,5,6};
	//从前往后遍历元素，对每个元素进行函数
	for_each(numbers.begin(),numbers.end(),print);
	cout<<endl;
	cout<<"-----------------"<<endl;
	//lambda代表的是匿名函数,[&]捕获前面定义的变量，(int number)
	//遍历for_each定义的每一个元素
	//{...}是对每一个元素和捕获的元素进行操作的函数
	for_each(numbers.begin(),numbers.end(),[&](int number)
	{
		cout<<number<<": a = "<<a++<<" ,b = "<<b++<<endl;
	});
	cout<<endl;
	cout<<"-----------------"<<endl;
	cout<<"a = "<<a<<endl;
	cout<<"b = "<<b<<endl;
}

void test2(void)
{
	vector<int> numbers{1,2,3,4,5,6};
	//把numbers里的3替换成7
	//std::replace(numbers.begin(),numbers.end(),3,7);
	std::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	cout<<"----------------"<<endl;
	//绑定模板函数lt，并指定这个绑定的参数是第几个参数lt(3,x)
	//然后在replace_if里面的第三个函数，如果返回true，就用第四个参数去替换
	std::less<int> lt;
	std::replace_if(numbers.begin(),numbers.end(),std::bind1st(lt,3),7);
	for(auto elem : numbers)
	{
		cout<<elem<<" ";
	}
	cout<<endl;
	cout<<"---------------"<<endl;
	std::replace_if(numbers.begin(),numbers.end(),std::bind2nd(lt,3),7);
	std::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
}

int main()
{
	//test1();
	test2();
	return 0;
}
