#ifndef AGILNET_NET_TCPACCEPT
#define AGILNET_NET_TCPACCEPT


#include <IOEventLoop.h>
#include <Socket.h>


namespace agilNet
{
namespace net
{

class TcpAccept
{
public:
    TcpAccept(IOEventLoop* loop);
    ~TcpAccept();
private:
    IOEventLoop* eventLoop;
    shared_ptr<Socket> socket;
    shared_ptr<IOEvent> event;
    bool listening;

    boost::function<void (int sockfd,const SocketAddr&)> newConnectCallback;

};

}
}

#endif // AGILNET_NET_TCPACCEPT
