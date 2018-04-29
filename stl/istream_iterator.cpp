 ///
 /// @file    istream_iterator.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-27 19:14:00
 ///
 
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::istream_iterator;
using std::ostream_iterator;

//用容器的观点来看待输入输出流
int main()
{
	vector<int> numbers;
	//输入流迭代器适配器
	istream_iterator<int> isi(std::cin);
	//输出结束的时候用临时对象去代表：istream_iterator<int>()
	//输出起始位置用isi代表
	std::copy(isi,istream_iterator<int>(),std::back_inserter(numbers));
	std::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	return 0;
}
