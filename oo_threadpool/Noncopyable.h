 ///
 /// @file    Noncopyable.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 15:33:22
 ///
 
#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__

namespace wd
{//继承该类的类不能进行复制，因为如果复制的话要先执行该类的复制控制函数
 //但是该类的复制控制函数被删除了。
	class Noncopyable
	{
		protected:
			Noncopyable(){}
			~Noncopyable(){}
			Noncopyable(const Noncopyable & rhs) = delete;
			Noncopyable & operator = (const Noncopyable &)=delete;
	};
}//end of namespace wd;

#endif

