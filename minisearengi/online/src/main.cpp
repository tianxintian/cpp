 ///
 /// @file    main.cpp
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-25 11:22:57
 ///
 

#include "Configuration.h"
#include "Acceptor.h"
#include "Wordqueryserver.h"
#include "SocketUtil.h"
#include "stdlib.h"
#include <iostream>

int main()
{
	Configuration _conf("./conf/my.conf");
	map<string,string> temp = _conf.get_config_map();
	Wordqueryserver wqs(_conf);
	wqs.start();
	return 0;
}
