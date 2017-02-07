#ifndef AGILNET_DOME_ECHOSERVER
#define AGILNET_DOME_ECHOSERVER

#include <TcpServer.h>



class EchoServer : public agilNet::net::TcpServer
{
public:
    EchoServer(agilNet::net::IOEventLoop* loop,agilNet::net::SocketAddr& addr);
    virtual void connectCallback(int sockfd,const agilNet::net::SocketAddr& addr);
    virtual void messageCallback();
    virtual void writeCompletCallback() ;
};

#endif // AGILNET_DOME_ECHOSERVER
