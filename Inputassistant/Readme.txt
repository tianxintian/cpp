mini_输入助手

<安装应用库>
1.cppjieba-->其中要把include里的Cppjieba文件夹放入linux系统/usr/include里。
2.log4cpp

<离线部分offline>
1.离线部分的读取文件建立字典，对中英文的词频统计，中文应用cppjieba处理
  建立索引共用索引函数，写入索引文件则共同使用存储函数。
2.运行方式是:cd src-->make 即可生成字典文件和索引文件，这里把中英文都放在一块。

<在线部分server>
1.在线部分应用线程池的框架，使用task运行任务函数。

2.读取配置文件，log4cpp日志记录，最小编辑距离算法，lrucache缓存，优先级队列存储结构体。

3.给客户端返回最优解。

4.运行方式是:make 

<客户端client>
1.运行方式:cd src --->cd client --->make

<总运行方式>
./bin/offline.exe 生成字典文件和索引文件
./bin/server.exe  启动服务器
./bin/client.exe  启动客户端

这里把客户端放在src里面，把离线部分拆开头文件和src文件，服务器在线部分也是这样做的。
