 ///
 /// @file    TimerThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-11 11:11:02
 ///
 
#include "TimerThread.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace wd;


TimerThread::TimerThread(int initialTime, int perodicTime, TimerCallback && cb)
: _timer(initialTime, perodicTime, std::move(cb))
, _thread(std::bind(&Timer::start, &_timer))
{
}

void TimerThread::start()
{
	_thread.start();
}

void TimerThread::stop()
{
	_timer.stop();
	_thread.join();
}

