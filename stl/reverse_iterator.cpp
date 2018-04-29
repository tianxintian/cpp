 ///
 /// @file    reverse_iterator.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-27 18:50:09
 ///
 
#include <iostream>
#include <vector>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;

int main(void)
{
	vector<int> numbers{1,2,3,4,5,6};
	//取得反向迭代器的开头和结尾
	vector<int>::reverse_iterator rit = numbers.rbegin();
	std::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	cout<<"-------------------"<<endl;
	std::copy(numbers.rbegin(),numbers.rend(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	cout<<"-------------------"<<endl;
	rit+=2;
	cout<<*rit<<endl;
	cout<<"-------------------"<<endl;
	while(rit != numbers.rend())
	{
		cout<<*rit<<" ";
		++rit;
	}
	cout<<endl;
	return 0;
}
