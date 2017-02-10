#ifndef AGILNET_NET_TCPCONNECT
#define AGILNET_NET_TCPCONNECT


#include <boost/shared_ptr.hpp>
#include <Socket.h>
#include <Buffer.h>
#include <boost/function.hpp>
#include <IOEventLoop.h>

namespace agilNet
{
namespace net
{
class TcpConnect
{
public:
    TcpConnect(IOEventLoop* l,struct sockaddr_in addr,int fd);
    ~TcpConnect();
    void setMessageCallback(boost::function<void (const TcpConnect&, Buffer&)> callback);
    const SocketAddr& getAddr() const;


private:
    IOEventLoop* loop;
    SocketAddr socketAddr;

    boost::shared_ptr<Socket> socket;
    boost::shared_ptr<IOEvent> event;

    void readFunction();
    boost::function<void (const TcpConnect&, Buffer&)> messageCallback;
    Buffer readBuf;

    const TcpConnect& getRefer();

    //boost::function<void (const TcpConnect&, Buffer*)> MessageCallback;
    //boost::function<void (const TcpConnect&, Buffer*)> MessageCallback;
};

}
}
#endif // AGILNET_NET_TCPCONNECT
