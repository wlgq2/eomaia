#ifndef AGILNET_DOME_ECHOSERVER
#define AGILNET_DOME_ECHOSERVER

#include <TcpServer.h>

using namespace agilNet::net;

class EchoServer : public TcpServer
{
public:
    EchoServer(IOEventLoop* loop,SocketAddr& addr);
    virtual void connectCallback(int sockfd,const SocketAddr& addr);
    virtual void messageCallback();
    virtual void writeCompletCallback() ;
};

#endif // AGILNET_DOME_ECHOSERVER
