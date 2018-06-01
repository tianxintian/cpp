 ///
 /// @file    Point3D2.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-01 18:12:54
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:
	Point(int ix=0,int iy=0)
	:_ix(ix)
	,_iy(iy)
	{
		cout<<"Point(int=0,int=0)"<<endl;
	}

	void print() const
	{
		cout<<"("<<_ix
			<<","<<_iy
			<<")"<<endl;
	}

	int getY()const
	{
		return _iy;
	}

protected:
	//protected成员的访问权限是直接开放给派生类
	int getX()const
	{
		return _ix;
	}

	int _ix;

private:
	int _iy;
};

class Point3D
:protected Point
{
public:
	Point3D(int ix,int iy,int iz)
	:Point(ix,iy)
	,_iz(iz)
	{
		cout<<"Point3D(int,int,int)"<<endl;
	}

	void display()const
	{//对于基类的public成员而言，使用protected继承时
	 //在派生类内部是protected，派生类可以直接访问
		print();
		//对于基类protected成员而言，使用protected继承时
		//在派生类内部是protected,派生类可以直接访问
		cout<<"("<<_ix
		//对于基类的私有成员，不能在派生类内部直接访问
		//需要借助于基类成员函数间接访问
			<<","<<getY()
			<<","<<_iz
			<<endl;
	}
private:
	int _iz;
};

int main(void)
{
	Point3D pt3d2(1,2,3);
	//只有public继承的时候才能用对象访问公有成员
	//pt3d2.print();
	//pt3d2.getX();
	//pt3d2.getY();
}
