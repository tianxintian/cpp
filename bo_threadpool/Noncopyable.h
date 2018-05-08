 ///
 /// @file    Noncopyable.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-08 19:19:20
 ///
 
#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__

namespace wd
{
	class Noncopyable//继承该类的类不能拷贝
	{
		protected:
			Noncopyable(){}
			~Noncopyable(){}
			Noncopyable(const Noncopyable & rhs)=delete;
			Noncopyable & operator=(const Noncopyable &)=delete;
	};
}//end of namespace wd

#endif

