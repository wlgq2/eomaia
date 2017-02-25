#ifndef AGILNET_NET_TCPCONNECT
#define AGILNET_NET_TCPCONNECT


#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <net/IOEventLoop.h>
#include <net/Socket.h>
#include <net/Buffer.h>

namespace agilNet
{
namespace net
{
class TcpConnect :public boost::enable_shared_from_this<TcpConnect>
{
public:
    TcpConnect(IOEventLoop* l,struct sockaddr_in addr,int fd);
    ~TcpConnect();
    void setMessageCallback(const boost::function<void ( boost::shared_ptr<TcpConnect>, Buffer&)> & callback);
    void setCloseCallback(const boost::function<void (boost::shared_ptr<TcpConnect>)> & callback);
    void setWriteCompletCallback(const boost::function<void (boost::shared_ptr<TcpConnect>)> & callback);

    const SocketAddr& getAddr() const;

    std::string getName() const;

    void write(const char* data);
    void write(const std::string& data);
    void write(const void* data,uint32_t length);
    void writeInLoop(const void* data, uint32_t len);
    void connectedHandle();

    void setNoDelay(bool enable);
    void shutdownWrite();
private:
    IOEventLoop* loop;
    SocketAddr socketAddr;
    std::string name;
    boost::shared_ptr<Socket> socket;
    boost::shared_ptr<IOEvent> event;

    void readEvent();
    void closeEvent();
    void writeEvent();
    void errorEvent();
    boost::function<void (boost::shared_ptr<TcpConnect>, Buffer&)> messageCallback;
    boost::function<void (boost::shared_ptr<TcpConnect>)> closeCallback;

    boost::function<void (boost::shared_ptr<TcpConnect>)> writeCompleteCallback;

    Buffer readBuf;
    Buffer writeBuf;
    TcpConnect& getRefer();


    int state;
    enum ConnectState { Disconnected, Connecting, Connected, Disconnecting };

};

}
}
#endif // AGILNET_NET_TCPCONNECT
