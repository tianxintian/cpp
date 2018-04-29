 ///
 /// @file    remove.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-27 18:21:18
 ///
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::remove;

int test0(void)
{
	vector<int> numbers{1,2,3,4,5,6,7,8,9,10};
	std::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	cout<<"--------------------------"<<endl;
	numbers[3] = numbers[6] = numbers[8] = 66;
	std::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	cout<<"-------------------------"<<endl;
	//remove是把删除的元素拿掉，把后面的数字往前推，留下本身的元素
	//返回值是迭代器，指向没删除元素的后一位，需要erase才能删除
	//remove(numbers.begin(),numbers.end(),66);
	//std::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(cout," "));
	//cout<<endl;
	//cout<<"-------------------------"<<endl;
	//用erase真正删除
	numbers.erase(remove(numbers.begin(),numbers.end(),66),numbers.end());
	std::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	return 0;
}

//在容器遍历的过程中，不要做删除或者添加元素的操作
void test1(void)
{
	vector<int> numbers{1,2};
	bool flag = true;
	for(auto it = numbers.begin();it != numbers.end();++it)
	{//遍历容器的过程中，添加元素可能会产生的异常的情况
		cout<<"numbers' size = "<<numbers.size()<<endl;
		cout<<"numbers' capacity = "<<numbers.capacity()<<endl;
		cout<<"*it = "<<*it<<endl;
		if(flag)
		{
			numbers.push_back(3);//底层发生了动态扩容，原来的迭代器it失效
			flag=false;
		}
	}
}

int main(void)
{
	//test0();
	test1();
	return 0;
}
