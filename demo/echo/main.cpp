#include <EchoServer.h>
#include <iostream>
#include <Log.h>
#include <IOEventLoop.h>
#include <IOEventLoopThread.h>

using namespace std;
using namespace agilNet::log;
using namespace agilNet::net;

int main()
{
    IOEventLoop loop;
    SocketAddr addr(true,10002);
    EchoServer server(&loop,addr);
    server.setThreadPoolSize(3);
    server.start();
    loop.run();

}
