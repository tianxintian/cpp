 ///
 /// @file    Timer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-11 10:01:40
 ///
 
#include "Timer.h"

#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <sys/timerfd.h>


#include <iostream>
using std::cout;
using std::endl;
using namespace wd;



Timer::Timer(int initialTime, int peroidicTime, TimerCallback && cb)
: _fd(createTimerfd())
, _initialTime(initialTime)
, _perodicTime(peroidicTime)
, _isStarted(false)
, _cb(std::move(cb))
{}

Timer::~Timer()
{
	if(_isStarted)
		stop();
}

void Timer::start()
{
	_isStarted = true;

	struct pollfd pfd;
	pfd.fd = _fd;
	pfd.events = POLLIN;

	setTimerfd(_initialTime, _perodicTime);//开启定时器

	while(_isStarted){
		int nready = poll(&pfd, 1, 5000);
		if(nready == -1)
		{
			if(errno == EINTR)
				continue;
			perror("poll error");
			return;
		}
		else if(nready == 0)
			cout << ">>> poll time out" << endl;
		else {
			if(pfd.revents & POLLIN)
			{
				handleRead();//处理定时器
				if(_cb)      // 执行任务
					_cb();
			}
		}
	}
}

void Timer::stop()
{
	if(_isStarted)
	{
		setTimerfd(0, 0);//停止定时器
		_isStarted = false;
	}
}


int Timer::createTimerfd()
{
	int fd = timerfd_create(CLOCK_REALTIME, 0);
	if(fd == -1)
	{
		perror("timerfd_create error");
	}
	return fd;
}
 

void Timer::setTimerfd(int initalTime, int perodicTime)
{
	struct itimerspec value;
	value.it_value.tv_sec = initalTime;
	value.it_value.tv_nsec = 0;
	value.it_interval.tv_sec = perodicTime;
	value.it_interval.tv_nsec = 0;

	int ret = timerfd_settime(_fd, 0, &value, NULL);
	if(ret == -1)
	{
		perror("timerfd_settime error");
	}
}

void Timer::handleRead()
{
	uint64_t howmany;
	int ret = read(_fd, &howmany, sizeof(howmany));
	if(ret != sizeof(uint64_t))
	{
		perror("read error");
	}
}
