 ///
 /// @file    mem_fn.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-27 14:30:53
 ///
 
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::for_each;
using std::remove_if;

class Number
{
public:
	Number(int value)
	:_value(value)
	{}

	void display() const
	{
		cout<<_value<<" ";
	}

	bool isEven() const
	{
		return (_value % 2 == 0);
	}

	bool isPrime()const
	{
		if(_value == 1)
		{
			return false;
		}
		for(int idx = 2; idx <= _value/2;++idx)
		{
			if(_value % idx == 0)
				return false;
		}
		return true;
	}
private:
	int _value;
};

int main()
{
	vector<Number> numbers;
	for(int idx = 1; idx != 20; ++idx)
	{
		numbers.push_back(Number(idx));
	}

	for_each(numbers.begin(),numbers.end(),std::mem_fn(&Number::display));
	cout<<endl;
	cout<<"-----------------------------"<<endl;
	//remove_if执行完返回往后移动元素的位置的迭代器
	numbers.erase(std::remove_if(numbers.begin(),numbers.end(),std::mem_fn(&Number::isPrime)),numbers.end());
	//for_each最后一个参数可以是一个成员函数适配器mem_fn()绑定
	for_each(numbers.begin(),numbers.end(),std::mem_fn(&Number::display));
	cout<<endl;
	return 0;
}
