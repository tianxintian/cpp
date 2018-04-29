 ///
 /// @file    stack.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-28 15:24:36
 ///
 
#include <iostream>
#include <stack>
#include <vector>
using std::cout;
using std::endl;
using std::stack;
using std::vector;
int main(void)
{
	//第二个参数表示存储int的容器，默认是deque
	stack<int,vector<int>> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	while(!st.empty())
	{
		cout<<st.top()<<" ";
		st.pop();
	}
	return 0;
}
