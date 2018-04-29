 ///
 /// @file    binary_search.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-27 10:04:50
 ///
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;

int main(void)
{
	vector<int> numbers{2,3,1,4,5,2,1,6,9,7,6,2,4,6};
	std::sort(numbers.begin(),numbers.end());
	std::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	cout<<"------------------------------"<<endl;
	//通过二分查找容器内是否有某个元素，格式化输出true或者false
	cout<<std::boolalpha<<std::binary_search(numbers.begin(),numbers.end(),10)<<endl;
	cout<<std::binary_search(numbers.begin(),numbers.end(),2)<<endl;
	cout<<"------------------------------"<<endl;
	//lower_bound()返回对应元素的迭代器，upper_bound()返回指向元素的下个位置迭代器
	auto it1=std::lower_bound(numbers.begin(),numbers.end(),2);
	auto it2=std::upper_bound(numbers.begin(),numbers.end(),2);
	while(it1 != it2)
	{
		cout<<*it1<<" ";
		++it1;
	}
	cout<<endl;
	//equal_range()返回元素的迭代器上下范围
	cout<<"------------------------------"<<endl;
	auto ret = std::equal_range(numbers.begin(),numbers.end(),2);
	while(ret.first != ret.second)
	{
		cout<<*ret.first<<" ";
		++ret.first;
	}
	cout<<endl;
	return 0;
}
