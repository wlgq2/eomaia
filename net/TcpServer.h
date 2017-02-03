#ifndef AGILNET_NET_TCPSERVER
#define AGILNET_NET_TCPSERVER

#include <AtomicInt.h>
#include <IOEventLoop.h>

namespace agilNet
{

namespace net
{

class TcpServer
{
public:
    TcpServer(IOEventLoop* loop);
    void start();
private:

    IOEventLoop* eventLoop;
    AtomicInt8 isStart;
};

}
}
#endif
