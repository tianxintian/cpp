 ///
 /// @file    secontainer1.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-25 10:49:47
 ///
 
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::list;

int test1()
{
	int arr[5]={10,11,12,13,14};
	vector<int> vecInt{1,2,3,4};
	cout<<"vector:";
	for(auto & number:vecInt)
	{
		cout<<number<<" ";
	}
	cout<<endl;
	cout<<"----------------------"<<endl;
	//vector支持随机访问，时间复杂度为O（1）
	cout<<vecInt[3]<<endl;
	cout<<"----------------------"<<endl;
	auto it = vecInt.begin();
	++it;
	//vector的insert时间复杂度是O（N）
	//vecInt.insert(it,5);
	std::copy(vecInt.begin(),vecInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	cout<<"----------------------"<<endl;
	cout<<"vecInt's size = "<<vecInt.size()<<endl;
	//只有vector拥有capacity()方法
	cout<<"vecInt's capacity = "<<vecInt.capacity()<<endl;
	cout<<"----------------------"<<endl;
	//在it指向的地方插入3个5
	//insert方法执行结束之后，it失效
	vecInt.insert(it,3,5);
	std::copy(vecInt.begin(),vecInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	cout<<"----------------------"<<endl;
	
	it=vecInt.begin();
	++it;
	vecInt.insert(it,arr,arr+5);
	std::copy(vecInt.begin(),vecInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	//push_back是O(1)
	vecInt.push_back(22);
	std::copy(vecInt.begin(),vecInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	it=vecInt.begin();
	++it;
	//erase时间复杂度为O(N)
	vecInt.erase(it);
	std::copy(vecInt.begin(),vecInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	cout<<"----------------------"<<endl;
	//清空所有的元素，但是并不会回收空间
	vecInt.clear();
	std::copy(vecInt.begin(),vecInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<"vecInt's size = "<<vecInt.size()<<endl;
	cout<<"vecInt's capacity = "<<vecInt.capacity()<<endl;
	cout<<"------------------------"<<endl;
	for(auto & number : vecInt)
	{
		cout<<number<<" ";
	}
	cout<<endl;
	cout<<"-------------------------"<<endl;

	list<int> liInt{1,2,3,4};
	cout<<"list:"<<endl;
	auto lit = liInt.begin();
	//时间复杂度为O（1）
	liInt.insert(lit,5);
	std::copy(liInt.begin(),liInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	liInt.insert(lit,3,5);
	std::copy(liInt.begin(),liInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	liInt.insert(lit,arr,arr+5);
	std::copy(liInt.begin(),liInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	//insert的时候迭代器会改变
	liInt.insert(lit,7);
	std::copy(liInt.begin(),liInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	liInt.push_front(0);
	liInt.push_back(33);
	std::copy(liInt.begin(),liInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	//list不支持随机访问
	

	deque<int> deInt{1,2,3,4};
	cout<<"deque:"<<endl;
	auto dit=deInt.begin();
	//deque的insert时间复杂度为O(N)
	deInt.insert(dit,5);
	std::copy(deInt.begin(),deInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	deInt.insert(dit,3,5);
	std::copy(deInt.begin(),deInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	deInt.insert(dit,arr,arr+5);
	std::copy(deInt.begin(),deInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	deInt.push_front(0);
	std::copy(deInt.begin(),deInt.end(),std::ostream_iterator<int>(cout," "));
	cout<<endl;
	deInt.push_back(33);

	for(auto & number: deInt)
	{
		cout<<number<<" ";
	}
	cout<<endl;
	cout<<endl;
	//deque支持随机访问
	cout<<deInt[0]<<endl;
	return 0;
}

int main()
{
	test1();
	return 0;
}
