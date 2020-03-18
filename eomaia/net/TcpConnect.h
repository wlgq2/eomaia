#ifndef EOMAIA_NET_TCPCONNECT
#define EOMAIA_NET_TCPCONNECT


#include <memory>
#include <functional>


#include <net/IOEventLoop.h>
#include <net/Socket.h>
#include <net/Buffer.h>

namespace eomaia
{
namespace net
{


class TcpConnect :public std::enable_shared_from_this<TcpConnect>
{
public:
    using OnMessageCallback = std::function<void (std::shared_ptr<TcpConnect>, Buffer&)>;
    using OnCloseCallback = std::function<void (std::shared_ptr<TcpConnect>)>;
    using OnWriteCompletCallback =std::function<void (std::shared_ptr<TcpConnect>)>;

public:
    TcpConnect(IOEventLoop* l,struct sockaddr_in addr,int fd);
    ~TcpConnect();
    void setMessageCallback(const OnMessageCallback callback);
    void setCloseCallback(const OnCloseCallback callback);
    void setWriteCompletCallback(const OnWriteCompletCallback callback);

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
    std::shared_ptr<Socket> socket;
    std::shared_ptr<IOEvent> event;

    void readEvent();
    void closeEvent();
    void writeEvent();
    void errorEvent();
    OnMessageCallback messageCallback;
    OnCloseCallback closeCallback;

    OnWriteCompletCallback writeCompleteCallback;

    Buffer readBuf;
    Buffer writeBuf;
    TcpConnect& getRefer();


    int state;
    enum ConnectState { Disconnected, Connecting, Connected, Disconnecting };

};

}
}
#endif // EOMAIA_NET_TCPCONNECT
