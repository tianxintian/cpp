 ///
 /// @file    Noncopyable.h
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-05-07 18:41:38
 ///
 
#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__

namespace wd
{
	class Noncopyable
	{
		protected:
			Noncopyable(){}
			~Noncopyable(){}
			Noncopyable(const Noncopyable & rhs)=delete;
			Noncopyable & operator=(const Noncopyable &) = delete;
	};
}//end of namespace wd

#endif
