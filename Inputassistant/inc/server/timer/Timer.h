 ///
 /// @file    Timer.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-11 09:59:07
 ///
 
#ifndef __WD_TIMER_H__
#define __WD_TIMER_H__

#include <functional>

 
namespace wd
{
class Timer
{
public:
	using TimerCallback = std::function<void()>;
	
	Timer(int initialTime, int perodicTime, TimerCallback && cb);
	~Timer();

	void start();
	void stop();
private:
	int createTimerfd();
	void setTimerfd(int initialTime, int perodicTime);
	void handleRead();

private:
	int _fd;
	int _initialTime;
	int _perodicTime;
	bool _isStarted;
	TimerCallback _cb;
};

}//end of namespace wd

#endif
