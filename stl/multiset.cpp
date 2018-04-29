 ///
 /// @file    multiset.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-27 23:55:40
 ///
 
#include <iostream>
#include <set>
#include <math.h>
using std::cout;
using std::endl;
using std::multiset;

template<typename Container>
void printContainer(const Container & container)
{//如果不特定的指出typename，嵌套从属名称，有可能产生解析歧义
 //任何时候在模板中指涉一个嵌套从属类型名称，需要在前一个位置
 //添加关键字typename
	typename Container::const_iterator cit = container.begin();
	while(cit != container.end())
	{
		cout<<*cit<<" ";
		++cit;
	}
	cout<<endl;
}

int test0(void)
{
	int arr[10] = {3,2,4,3,1,2,6,7,6,5};
	//multiset之中能存放关键字相同的元素
	//默认情况下以升序的方式进行排列
	//因为默认情况下指定了operator<的比较方式
	//multiset不支持下标访问运算符
	//添加进set的元素不能被修改
	multiset<int> multisetInt(arr,arr+10);
	cout<<"multiset's size = "<<multisetInt.size()<<endl;
	printContainer(multisetInt);
	cout<<"--------------------"<<endl;
	return 0;
}

int test1(void)
{
	int arr[10] = {3,2,4,3,1,2,6,7,6,5};
	//multiset可以指定排序方式,greater是从大到小
	multiset<int,std::greater<int>> multisetInt(arr,arr+10);
	cout<<"multiset'size = "<<multisetInt.size()<<endl;
	printContainer(multisetInt);
	return 0;
}

class Point
{
public:
	Point(int ix=0,int iy=0)
	:_ix(ix)
	,_iy(iy)
	{
		cout<<"Point(int=0,int=0)"<<endl;
	}

	Point(const Point & rhs)
	:_ix(rhs._ix)
	,_iy(rhs._iy)
	{
		cout<<"Point(const Point &)"<<endl;
	}

	void multiset(int ix,int iy)
	{
		_ix=ix;
		_iy=iy;
	}

	double length() const
	{
		return sqrt(pow(_ix,2)+pow(_iy,2));
	}

	~Point()
	{
		cout<<"~Point()"<<endl;
	}
	friend std::ostream & operator<<(std::ostream & os,const Point & rhs);
	friend bool operator<(const Point & lhs,const Point & rhs);
	friend bool operator>(const Point & lhs,const Point & rhs);
private:
	int _ix;
	int _iy;
};


std::ostream & operator<<(std::ostream & os,const Point & rhs)
{
	os<<"("<<rhs._ix
	  <<","<<rhs._iy
	  <<")";
	return os;
}

bool operator<(const Point & lhs,const Point & rhs)
{
	return lhs.length()<rhs.length();
}

bool operator>(const Point & lhs,const Point & rhs)
{
	return lhs.length()>rhs.length();
}

int test2(void)
{
	multiset<Point,std::greater<Point>> points{
		Point(1,2),
		Point(3,4),
		Point(5,6),
		Point(1,2)
	};
	printContainer(points);
	return 0;
}


int main(void)
{
	//test0();
	//test1();
	test2();
	return 0;
}
