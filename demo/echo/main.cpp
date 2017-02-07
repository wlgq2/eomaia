#include <EchoServer.h>

#include <Log.h>
using namespace agilNet::support;
int main()
{
    Log::getSingle()->write(Log::error,"ftgytgfhtfd woyaode jius zhez ganje");
#if 0
    IOEventLoop loop;
    SocketAddr addr(true,10002);
    EchoServer server(&loop,addr);
    server.start();
    loop.run();
    #endif // 0
}
