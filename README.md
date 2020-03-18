# eomaia
一个基Reactor模式+epoll复用机制实现的C++网络库，无任何依赖，基于C++11（需要g++5以上），支持one loop per thread。  参考学习陈硕的muduo<br>



## 编译
<br>提供codeblocks与Cmake两种方式编译。</br>
* codeblocks 编译： 
1.  `apt-get install codeblocks`
2.  用codeblocks打开example目录下工程，点击build即可。
* cmake编译： 
1.  `mkdir build`
2.  `cd build`
3.  `cmake ..`
4.  将头文件与.so、.a文件加入工程。

## 目录结构
1.`example` 相关测试例程 <br>
2.`eomaia/net` 网络库的主要实现，包括reactor模式实现与TCP相关类封装<br>
3.`eomaia/base` 网络库的依赖，封装log接口、线程/线程池<br>


## reactor模式实现细节  
1.`Epoll类`  :对linux epoll的封装，包括对epoll添加/删除/修改事件，以及调用wait操作等待事件<br>
2.`IOEvent类`:对事件的封装，包括一个文件fd成员变量，以及相关读写事件处理函数。所有需要响应事件的类都在内部包含一个IOEvent成员变量对象，并注册到loop中<br>
3.`IOEventCtrl类`: 内部包含一个IOEvent事件池，该类把事件注册到Epoll中，并调用waitAndRunHandle()等待并获得事件触发，并调用事件池中的事件回调函数<br>
4.`IOEventLoop类`: 事件循环类，一个事件循环类对应一个线程，内部包含一个IOEventCtrl成员变量，在run()函数中调用该成员变量等待/执行事件<br>


## Tcp相关类封装
1.`TcpAccept` : 内部包括一个成员变量Socket对象，以及IOevent类，当有新连接时触发事件<br>
2.`TcpConnec` : TCP连接类，代表一次新的连接。当服务器与连接读写数据时触发事件<br>
3.`TcpServer` : Tcp服务器，内部包括一个 TcpConnect池，有新的连接时候向该池增加Tcpconnect对象，当连接断开时在池中删掉该对象<br>
4.`Buffer`    : 对缓存的封装<br>
5 `Socket 与SocketOperation` : socket 与socket操作的封装<br>


## 定时器列队实现原理
1.在TimerQueue类中初始化一个timerFd，并加入epoll事件中等待触发<br>
2.考虑到可能会有多个相同时间的定时器，TimerQueue中有两个multimap容器：onceTimers和everyTimers，分别是定时只运行一次的事件，和定隔每次运行的事件<br>
3.每次添加定时器容器，如果加入事件比容器中时间最近的事件还近，则重置定时器为新添加事件<br>
4.定时器事件被触发时，执行设置时间小于当前时间的定时器回调函数，并删除列队。如果间隔每次触发的事件，则删除元素后，更新时间重新添加。<br>


## One loop per thread机制支持
1.`base/Thread类`  ：把std::thead封装成类似Qt/QThead,用户线程需继承Thread类，实现纯虚函数run(),并调用start()启动线程。<br>
2.`net/IOEventLoopThread类`  ：Thread类的子类，实现具体业务逻辑，对应一个IOEventLoop事件循环，并在IOEventLoop记录当前线程ID。<br>
3.`net/IOEventLoopThreadPool类`  ：线程池类，有新连接建立时，从线程池中分配一个线程给该TCP连接使用。<br>

## 例程与使用
* `example/echo`： 回显服务器。
* `example/http`： http服务demo。
* `example/timer`: 定时器使用例程。
