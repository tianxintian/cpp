 ///
 /// @file    not1.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-29 20:44:06
 ///
 
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;
typedef vector<int> VI;
typedef vector<int>::iterator VIP;

int main(void)
{
	int sz[]={1,2,3,4,5,6};
	VI ob(sz,sz+6);
	//创建less<int>类对象
	less<int> lt;
	//1 2 7 7 7 7
	replace_if(ob.begin(),ob.end(),not1(bind2nd(lt,3)),7);

	for(VIP v=ob.begin();v!=ob.end();v++)
	{
		cout<<(*v)<<" ";
	}
	cout<<endl;
	getchar();
	return 0;
}
