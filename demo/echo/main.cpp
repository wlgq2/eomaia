#include <EchoServer.h>


int main()
{
    IOEventLoop loop;
    SocketAddr addr(true,10002);
    EchoServer server(&loop,addr);
    server.start();
    loop.run();
}
