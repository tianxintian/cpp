 ///
 /// @file    set_intersection.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-27 19:04:03
 ///
 
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;

int main(void)
{
	vector<int> numbers1{1,2,3,4,5,6};
	vector<int> numbers2{3,5,7,9};

	//第五个参数用输出迭代器输出
	std::set_intersection(
			numbers1.begin(),numbers1.end(),
			numbers2.begin(),numbers2.end(),
			std::ostream_iterator<int>(cout," ")
			);
	cout<<endl;
	cout<<"-------------------"<<endl;

	//第五个参数用输出迭代器输出
	std::set_difference(
			numbers1.begin(),numbers1.end(),
			numbers2.begin(),numbers2.end(),
			std::ostream_iterator<int>(cout," ")
			);
	cout<<endl;

	return 0;
}
