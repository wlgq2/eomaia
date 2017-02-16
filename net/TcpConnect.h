#ifndef AGILNET_NET_TCPCONNECT
#define AGILNET_NET_TCPCONNECT


#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include <net/IOEventLoop.h>
#include <net/Socket.h>
#include <net/Buffer.h>

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
    void setWriteCompletCallback(boost::function<void (const TcpConnect&)> callback);

    const SocketAddr& getAddr() const;

    std::string getName() const;

    void writeInLoop(const void* data, uint32_t len);
    void connectedHandle();

    void setNoDelay(bool enable);
private:
    IOEventLoop* loop;
    SocketAddr socketAddr;
    std::string name;
    boost::shared_ptr<Socket> socket;
    boost::shared_ptr<IOEvent> event;

    void readEvent();
    void closeEvent();
    void writeEvent();
    boost::function<void (const TcpConnect&, Buffer&)> messageCallback;
    boost::function<void (const TcpConnect&)> closeCallback;

    boost::function<void (const TcpConnect&)> writeCompleteCallback;

    Buffer readBuf;
    Buffer writeBuf;
    const TcpConnect& getRefer();


    int state;
    enum ConnectState { Disconnected, Connecting, Connected, Disconnecting };

};

}
}
#endif // AGILNET_NET_TCPCONNECT
