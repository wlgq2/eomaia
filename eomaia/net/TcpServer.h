#ifndef EOMAIA_NET_TCPSERVER
#define EOMAIA_NET_TCPSERVER

#include <map>
#include <atomic>

#include <net/IOEventLoop.h>
#include <net/TcpAccept.h>
#include <net/TcpConnect.h>
#include <net/IOEventLoopThreadPool.h>


namespace eomaia
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
    virtual void connectCallback(std::shared_ptr<TcpConnect> tcpConnect)=0;
    virtual void messageCallback(std::shared_ptr<TcpConnect>, Buffer&)=0;
    virtual void writeCompletCallback(std::shared_ptr<TcpConnect> tcpConnect) = 0;
    virtual void connectCloseCallback(std::shared_ptr<TcpConnect>)=0;

    void addConnect(std::string name,std::shared_ptr<TcpConnect> connect);
    void addConnect(std::string name,TcpConnect* connect);
    bool haveConect(std::string name);
    void removeConnect(std::string name);
    long getConnectCount();

    void write(TcpConnect& connect,void* data,uint32_t length);
    void write(std::string& name,void* data,uint32_t length);
    void write(std::shared_ptr<TcpConnect> connect,void* data,uint32_t length);
    void write(std::string& name,std::string& data);
    void setThreadPoolSize(uint16_t num);
private:
    void newConnected(int sockfd,const SocketAddr& addr);
    IOEventLoop* eventLoop;
    SocketAddr tcpAddr;
    std::shared_ptr<TcpAccept> tcpAccept;

    std::map<std::string,std::shared_ptr<TcpConnect> >connectPool;
    void connectCloseEvent(std::shared_ptr<TcpConnect> connect);
    std::atomic<bool> isStart;

    std::shared_ptr<IOEventLoopThreadPool> threadPool;
};

}
}
#endif
