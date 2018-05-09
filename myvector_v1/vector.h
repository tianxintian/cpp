 ///
 /// @file    vector.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-26 18:41:12
 ///
 
#include <iostream>
#include <memory>
using std::cout;
using std::endl;

template<typename T>
class Vector
{
	public:
	Vector();
	~Vector();
	
	void push_back(const T &);
	void pop_back();

	int size() const;
	int capacity() const;

private:
	void reallocate();

private:
	static std::allocator<T> _alloc;

	T * _start;
	T * _finish;
	T * _end_of_storage;
};

template<typename T>
std::allocator<T> Vector<T>::_alloc;

template<typename T>
Vector<T>::Vector()
:_start(NULL)
,_finish(NULL)
,_end_of_storage(NULL)
{}

template<typename T>
Vector<T>::~Vector()
{
	if(_start)
	{
		while(_start != _finish)
		{
			_alloc.destroy(--_finish);
		}
		_alloc.deallocate(_start,capacity());
	}
}

template<typename T>
void Vector<T>::push_back(const T & value )
{
	if(size() == capacity()) 
	{
		reallocate();
	}
	_alloc.construct(_finish++,value);
}

template<typename T>
void Vector<T>::pop_back()
{
	if(size() > 0)
	{
		_alloc.destroy(--_finish);
	}
}

template<typename T>
int Vector<T>::size() const
{
	return _finish-_start;
}

template<typename T>
int Vector<T>::capacity()const
{
	return _end_of_storage - _start;
}

template<typename T>
void Vector<T>::reallocate()
{
	int oldCapacity = capacity();
	int newCapacity = oldCapacity == 0 ? 1 : oldCapacity * 2;
	T * newElements = _alloc.allocate(newCapacity);
	if(_start)
	{
		std::uninitialized_copy(_start,_finish,newElements);
		while(_start != _finish)
		{
			_alloc.destroy(--_finish);//变成未类型化的空间
		}
		_alloc.deallocate(_start,oldCapacity);//释放以前的全部未类型化的空间
	}
	_start = newElements;
	_finish=_start + oldCapacity;
	_end_of_storage = _start + newCapacity;
}

void display(Vector<int> & vec)
{
	cout<<"vec's size = "<<vec.size()<<endl;
	cout<<"vec's capacity = "<<vec.capacity()<<endl;
}

