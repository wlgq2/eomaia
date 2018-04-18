#include "EchoServer.h"
#include <iostream>
#include <support/Log.h>
#include <net/IOEventLoop.h>
#include <net/IOEventLoopThread.h>

using namespace std;
using namespace agilNet::log;
using namespace agilNet::net;

int main()
{
    //创建主循环事件分发器
    IOEventLoop loop;

    //监听地址和端口
    SocketAddr addr(true,10002);

    //创建服务器
    EchoServer server(&loop,addr);

    //设置线程池大小
    server.setThreadPoolSize(3);

    //服务器开始运行
    server.start();

    //事件循环机制运行
    loop.run();
}
