 ///
 /// @file    TimerThread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-11 11:08:45
 ///
 
#ifndef __WD_TIMER_THREAD_H__
#define __WD_TIMER_THREAD_H__

#include "Thread.h"
#include "Timer.h"

namespace wd
{

class TimerThread
{
public:
	using TimerCallback = std::function<void()>;
	TimerThread(int initialTime, int perodicTime, TimerCallback && cb);

	void start();
	void stop();
private:
	Timer _timer;
	Thread _thread;
};

}


#endif
