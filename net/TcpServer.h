#ifndef AGILNET_NET_TCPSERVER
#define AGILNET_NET_TCPSERVER

#include <AtomicInt.h>
#include <IOEventLoop.h>
#include <TcpAccept.h>

namespace agilNet
{

namespace net
{

class TcpServer
{
public:
    TcpServer(IOEventLoop* loop,SocketAddr& addr);
    //TcpServer 是个总是被继承的类，虚析构函数比较安全。
    virtual ~TcpServer();
    void start();
    virtual void connectCallback(int sockfd,const SocketAddr& addr)=0;
    virtual void messageCallback()=0;
    virtual void writeCompletCallback() = 0;
private:

    IOEventLoop* eventLoop;
    SocketAddr tcpAddr;
    boost::shared_ptr<TcpAccept> tcpAccept;
    AtomicInt8 isStart;
};

}
}
#endif
