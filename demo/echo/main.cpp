#include <EchoServer.h>
#include <iostream>
#include <Log.h>
#include <IOEventLoop.h>

using namespace std;
using namespace agilNet::support;
using namespace agilNet::net;

int main()
{
    IOEventLoop loop;
    SocketAddr addr(true,10002);
    EchoServer server(&loop,addr);
    server.start();
    loop.run();

}
