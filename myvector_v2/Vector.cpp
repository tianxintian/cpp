 ///
 /// @file    Vector.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-28 21:19:54
 ///
 
#include <iostream>
#include <memory>
#include <algorithm>
using std::cout;
using std::endl;

template<typename T>
class Vector
{
public:
	typedef T value_type;
	typedef T * iterator;
	typedef const T * const_iterator;

	Vector()
	:_start(NULL)
	,_finish(NULL)
	,_end_of_storage(NULL)
	{}

	~Vector();
	
	void push_back(const T & value);
	void pop_back();

	const_iterator begin() const{return _start;}
	const_iterator end() const{return _finish;}

	size_t size() const{return _finish - _start;}
	size_t capacity() const{return _end_of_storage - _start;}

private:
	void reallocate();//动态扩容，重新分配内存
	static std::allocator<T> _alloc;
private:
	T * _start;
	T * _finish;
	T * _end_of_storage;
};

template<typename T>
std::allocator<T> Vector<T>::_alloc;

template<typename T>
Vector<T>::~Vector()
{
	while(_start != _finish)
	{//析构这些类型化的数据
		_alloc.destroy(--_finish);
	}
	if(_start)
	{//释放空间
		_alloc.deallocate(_start,capacity());
	}
}

template<typename T>
void Vector<T>::push_back(const T & value)
{//若空间分配完，重新分配空间
	if(size() == capacity())
	{
		reallocate();
	}
	//若空间没满，分配一个，传指针和值
	_alloc.construct(_finish++,value);
}

template<typename T>
void Vector<T>::pop_back()
{
	if(size())
	{//析构这个类型即可
		_alloc.destory(--_finish);
	}
}

template<typename T>
void Vector<T>::reallocate()
{
	size_t cap = capacity();
	size_t newCap = cap ? 2 * cap: 1;
	T * newStart = _alloc.allocate(newCap);
	//不能调用copy函数
	//因为copy函数调用了对象的赋值运算符函数
	//而此时对象还未创建
	//std::copy(_start,_finish,newStart);
	if(_start)
	{
		std::uninitialized_copy(_start,_finish,newStart);

		while(_start != _finish)
		{
			_alloc.destroy(--_finish);
		}
		_alloc.deallocate(_start,cap);
	}
	_start = newStart;
	_finish = newStart+cap;
	_end_of_storage = newStart + newCap;
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

void printCapacity(const Vector<Point> & points)
{
	cout<<"points's size = "<<points.size()<<endl;
	cout<<"points's capacity = "<<points.capacity()<<endl;
}

void printVector(const Vector<Point> & points)
{
	for(auto & elem :points)
	{
		cout<<elem<<endl;
	}
}

int main(void)
{
	Vector<Point> points;
	printCapacity(points);

	points.push_back(Point(1,2));
	printCapacity(points);

	points.push_back(Point(3,4));
	printCapacity(points);

	points.push_back(Point(5,6));
	printCapacity(points);

	printVector(points);
	return 0;
}





