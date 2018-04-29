 ///
 /// @file    ostream_iterator.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-27 19:40:27
 ///
 
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::ostream_iterator;

int main(void)
{
	vector<int> numbers{1,2,3,4,5,6};
	//输出流迭代器 做写操作
	//
	//ostream_iterator是一个迭代器适配器
	ostream_iterator<int> osi(cout," ");
	std::copy(numbers.begin(),numbers.end(),osi);
	cout<<endl;

	return 0;
}
