 ///
 /// @file    main.cpp
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-23 01:08:30
 ///
 

#include "Configuration.h"
#include "DirScanner.h"
#include "PageLib.h"
#include "WebPage.h"
#include "PageLibPreprocessor.h"
#include "WordSegmentation.h"
#include <stdio.h>
#include <time.h>

int main()
{
	Configuration conf("./conf/my.conf");
	DirScanner dirScanner(conf);
	dirScanner();
	PageLib pagelib(conf,dirScanner);

	time_t t1=time(NULL);
	//这里是原始库
	pagelib.create();
	pagelib.store();
	time_t t2=time(NULL);
	printf("raw lib create and store time is :%ld min\n",t2-t1);

	PageLibPreprocessor libPreprocessor(conf);
	//这里面是去重，然后建立三个要用的库
	libPreprocessor.doProcess();
	return 0;
}
