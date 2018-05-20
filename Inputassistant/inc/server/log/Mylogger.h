 ///
 /// @file    Mylogger.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-16 14:40:05
 ///
 
#ifndef __WD_MYLOGGER_H__
#define __WD_MYLOGGER_H__

#include <string>
#include <sstream>
#include <log4cpp/Category.hh>
using std::string;


class Mylogger
{
public:
	enum Priority
	{
		ERROR,
		WARN,
		INFO,
		DEBUG
	};

	static Mylogger * getInstance();
	static void destroy();

	void error(const char * msg);

	template <typename... Args>
	void error(const char * msg, Args... args){
		_root.error(msg, args...);
	}

	void warn(const char * msg);
	template <typename... Args>
	void warn(const char * msg, Args...args){
		_root.warn(msg, args...);
	}

	void info(const char * msg);
	template <typename... Args>
	void info(const char * msg, Args... args){
		_root.info(msg, args...);
	}

	void debug(const char * msg);
	template <typename... Args>
	void debug(const char * msg, Args... args){
		_root.debug(msg, args...);
	}

	void setPriority(Priority priority);
private:
	Mylogger();
	~Mylogger();
	
private:
	static Mylogger * _pInstance;
	log4cpp::Category & _root;
};


inline void initMylogger(Mylogger::Priority priority)
{
	Mylogger::getInstance()->setPriority(priority);
}


inline string int2str(int number)
{
	std::ostringstream oss;
	oss << number;
	return oss.str();
}

#define prefix(msg) string("[").append(__FILE__)\
		.append(":").append(__FUNCTION__)\
		.append(":").append(int2str(__LINE__))\
		.append("] ").append(msg).c_str()

//可变参数宏, 字符串替换
#define LogWarn(msg, ...)  Mylogger::getInstance()->warn(prefix(msg), ##__VA_ARGS__)
#define LogError(msg, ...)  Mylogger::getInstance()->error(prefix(msg), ##__VA_ARGS__)
#define LogInfo(msg, ...)  Mylogger::getInstance()->info(prefix(msg), ##__VA_ARGS__)
#define LogDebug(msg, ...)  Mylogger::getInstance()->debug(prefix(msg), ##__VA_ARGS__)

#endif
