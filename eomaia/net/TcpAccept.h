#ifndef EOMAIA_NET_TCPACCEPT
#define EOMAIA_NET_TCPACCEPT

#include <functional>

#include <net/IOEventLoop.h>
#include <net/Socket.h>


namespace eomaia
{
namespace net
{
using NewConnectCallback = std::function<void (int sockfd,const SocketAddr&)> ;

class TcpAccept
{
public:
    TcpAccept(IOEventLoop* loop,SocketAddr& addr);
    ~TcpAccept();
    void listen();
    bool isListen();
    void setNewConnectCallback(const NewConnectCallback callback);
private:
    IOEventLoop* eventLoop;
    std::shared_ptr<Socket> socket;
    std::shared_ptr<IOEvent> event;
    bool listening;

    void acceptHandle();
    NewConnectCallback newConnectCallback;

};

}
}

#endif // EOMAIA_NET_TCPACCEPT
