 ///
 /// @file    Mylogger.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-04-16 14:42:57
 ///
 
#include "Mylogger.h"
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>

#include <iostream>
using std::cout;
using std::endl;


Mylogger * Mylogger::_pInstance = nullptr;

Mylogger * Mylogger::getInstance()
{
	if(nullptr == _pInstance)
	{
		_pInstance = new Mylogger();
	}
	return _pInstance;
}


void Mylogger::destroy()
{
	if(_pInstance)
	{
		delete _pInstance;
	}
}

Mylogger::Mylogger()
: _root(log4cpp::Category::getRoot())
{
	log4cpp::PatternLayout * pt1 = new log4cpp::PatternLayout();
	pt1->setConversionPattern("[%d] [%p] %m%n");

	log4cpp::PatternLayout * pt2 = new log4cpp::PatternLayout();
	pt2->setConversionPattern("[%d] [%p] %m%n");

	log4cpp::OstreamAppender * ostreamAppender = new log4cpp::OstreamAppender("ostreamAppender", &cout);
	ostreamAppender->setLayout(pt1);

	log4cpp::FileAppender * fileAppender = new log4cpp::FileAppender("fileAppender", "./log/my.log");
	fileAppender->setLayout(pt2);

	_root.addAppender(ostreamAppender);
	_root.addAppender(fileAppender);
	_root.setPriority(log4cpp::Priority::DEBUG);
	//cout << "Mylogger()" << endl;
}

Mylogger::~Mylogger()
{
	cout << "~Mylogger()" << endl;
	log4cpp::Category::shutdown();
}

void Mylogger::setPriority(Priority priority)
{
	switch(priority)
	{
		case ERROR:
			_root.setPriority(log4cpp::Priority::ERROR);
			break;
		case WARN:
			_root.setPriority(log4cpp::Priority::WARN);
			break;
		case INFO:
			_root.setPriority(log4cpp::Priority::INFO);
			break;
		case DEBUG:
			_root.setPriority(log4cpp::Priority::DEBUG);
			break;
	}
}

void Mylogger::warn(const char * msg)
{
	_root.warn(msg);
}
void Mylogger::error(const char * msg)
{
	_root.error(msg);
}
void Mylogger::info(const char * msg)
{
	_root.info(msg);
}
void Mylogger::debug(const char * msg)
{
	_root.debug(msg);
}
