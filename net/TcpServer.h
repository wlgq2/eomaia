#ifndef AGILNET_NET_TCPSERVER
#define AGILNET_NET_TCPSERVER

#include <map>
#include <support/AtomicInt.h>

#include <net/IOEventLoop.h>
#include <net/TcpAccept.h>
#include <net/TcpConnect.h>
#include <net/IOEventLoopThreadPool.h>


namespace agilNet
{

namespace net
{

class TcpServer
{
public:
    TcpServer(IOEventLoop* loop,SocketAddr& addr);
    //TcpServer 是个总是被继承的类，虚析构函数比较安全。
    virtual ~TcpServer();
    void start();
    virtual void connectCallback(int sockfd,const SocketAddr& addr)=0;
    virtual void messageCallback(const TcpConnect&, Buffer&)=0;
    virtual void writeCompletCallback() = 0;
    virtual void connectCloseCallback(const TcpConnect&)=0;

    void addConnect(std::string name,boost::shared_ptr<TcpConnect> connect);
    void addConnect(std::string name,TcpConnect* connect);
    bool haveConect(std::string name);
    void removeConnect(std::string name);
    long getConnectCount();

    void write(TcpConnect& connect,void* data,uint32_t length);
    void write(std::string name,void* data,uint32_t length);
    void write(boost::shared_ptr<TcpConnect> connect,void* data,uint32_t length);
    void write(std::string name,std::string data);
    void setThreadPoolSize(uint16_t num);
private:
    void newConnected(int sockfd,const SocketAddr& addr);
    IOEventLoop* eventLoop;
    SocketAddr tcpAddr;
    boost::shared_ptr<TcpAccept> tcpAccept;

    std::map<std::string,boost::shared_ptr<TcpConnect> >connectPool;
    void connectCloseEvent(const TcpConnect& connect);
    AtomicInt8 isStart;

    boost::shared_ptr<IOEventLoopThreadPool> threadPool;
};

}
}
#endif
