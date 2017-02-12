# agilNet
一个基于reactor模式+epoll复用机制的C++网络库，支持one loop per thread。 



一.目录结构
1.demo 相关测试例程，目前只包括一个回显服务器。

2.net 网络库的主要实现，包括reactor模式实现与TCP相关类封装

3.support 网络库的依赖，包括log，线程同步机制，及线程/线程池。 


二.reactor模式实现细节  

1.Epoll类:对linux epoll的封装，包括对epoll添加/删除/修改事件，以及调用wait操作等待事件。
2.IOEvent类:对事件的封装，包括一个文件fd成员变量，以及相关读写事件处理函数。所有需要响应事件的类都在内部包含一个IOEvent成员变量对象，并注册到loop中。
3.IOEventCtrl类: 内部包含一个IOEvent事件池，该类把事件注册到Epoll中，并调用waitAndRunHandle()等待并获得事件触发，并调用事件池中的事件回调函数。
4.IOEventLoop类: 事件循环类，一个事件循环类对应一个线程，内部包含一个IOEventCtrl成员变量，在run()函数中调用该成员变量等待/执行事件。


三.Tcp相关类封装

1.TcpAccept : 内部包括一个成员变量Socket对象，以及IOevent类，当有新连接时触发事件。
2.TcpConnec : TCP连接类，代表一次新的连接。当服务器与连接读写数据时触发事件。
3.TcpServer : Tcp服务器，内部包括一个 TcpConnect池，有新的连接时候向该池增加Tcpconnect对象，当连接断开时在池中删掉该对象。
4.Buffer    : 对缓存的封装
5 Socket 与SocketOperation : socket 与socket操作的封装。


四.关于该库的使用
简单的说，只要继承自TcpServer类并实现几个虚事件函数即可.详见dome文件夹。
