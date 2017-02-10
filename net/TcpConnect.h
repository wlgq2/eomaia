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
    void setCloseCallback(boost::function<void (const TcpConnect&)> callback);


    const SocketAddr& getAddr() const;

    std::string getName() const;
private:
    IOEventLoop* loop;
    SocketAddr socketAddr;
    std::string name;
    boost::shared_ptr<Socket> socket;
    boost::shared_ptr<IOEvent> event;

    void readEvent();
    void closeEvent();
    boost::function<void (const TcpConnect&, Buffer&)> messageCallback;
    boost::function<void (const TcpConnect&)> closeCallback;

    Buffer readBuf;

    const TcpConnect& getRefer();

    //boost::function<void (const TcpConnect&, Buffer*)> MessageCallback;
    //boost::function<void (const TcpConnect&, Buffer*)> MessageCallback;
};

}
}
#endif // AGILNET_NET_TCPCONNECT
