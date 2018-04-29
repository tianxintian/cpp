 ///
 /// @file    list.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-27 19:56:52
 ///
 
#include <iostream>
#include <list>
#include <vector>
using std::cout;
using std::endl;
using std::list;
using std::vector;

int test0(void)
{
	int arr[3]={4,5,6};
	list<int> liInt{1,2,3};
	list<int>::iterator it = liInt.begin();
	*it = 0;
	
	liInt.insert(it,arr,arr+3);
	for(auto & number :liInt)
	{
		cout<<number <<" ";
	}
	cout<<endl;

	list<int>::iterator lit;
	for(lit = liInt.begin(); lit !=liInt.end();++lit)
	{
		cout<<*lit<<" ";
	}
	cout<<endl;
	return 0;

}

int test1(void)
{
	vector<int> vecInt{1,2,3};
	vecInt.push_back(4);
	cout<<"size = "<<vecInt.size()<<endl;
	cout<<"capacity = "<<vecInt.capacity()<<endl;
	//回收多余的空间
	vecInt.shrink_to_fit();
	cout<<"size = "<<vecInt.size()<<endl;
	cout<<"capacity = "<<vecInt.capacity()<<endl;
	return 0;
}

class Point
{
public:
	Point(int ix = 0,int iy = 0)
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

	void set(int ix,int iy)
	{
		_ix=ix;
		_iy=iy;
	}

	~Point()
	{
		cout<<"~Point()"<<endl;
	}

	friend std::ostream & operator<<(std::ostream & os,const Point & rhs);
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

void test2(void)
{
	//申请的时候发生了拷贝，先构造再拷贝，再把构造的析构了
	//十一次构造，十一次拷贝，十次析构掉申请的，再析构掉十一次对象
	//因为已经拷贝进容器了
	vector<Point> points(10);
	Point pt1(1,2);
	//放入容器中的元素都是一个全新的副本copy
	points.push_back(pt1);
	pt1.set(3,4);
	for(auto & point : points)
	{
		cout<<point<<" ";
	}
	cout<<endl;
	cout<<"pt1 = "<<pt1<<endl;
}


int main(void)
{
	//test0();
	//test1();
	test2();
	return 0;
}
