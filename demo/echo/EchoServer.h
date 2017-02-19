#ifndef AGILNET_DOME_ECHOSERVER
#define AGILNET_DOME_ECHOSERVER

#include <net/TcpServer.h>



class EchoServer : public agilNet::net::TcpServer
{
public:
    EchoServer(agilNet::net::IOEventLoop* loop,agilNet::net::SocketAddr& addr);
    virtual void connectCallback(agilNet::net::TcpConnect& tcpConnect);
    virtual void messageCallback(const agilNet::net::TcpConnect&, agilNet::net::Buffer&);
    virtual void writeCompletCallback() ;
    virtual void connectCloseCallback(const agilNet::net::TcpConnect&);
};

#endif // AGILNET_DOME_ECHOSERVER
