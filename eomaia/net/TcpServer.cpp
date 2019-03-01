#include <net/TcpServer.h>
#include <thread>
#include <base/LogInterface.h>


using namespace eomaia::net;
using namespace std;


TcpServer::TcpServer(IOEventLoop* loop,SocketAddr& addr)
    :eventLoop(loop),
    tcpAddr(addr),
    tcpAccept(new TcpAccept(loop,addr)),
    isStart(false),
    threadPool(new IOEventLoopThreadPool(loop))
{
    tcpAccept->setNewConnectCallback(std::bind(&TcpServer::newConnected,this,std::placeholders::_1,std::placeholders::_2));
}


TcpServer::~TcpServer()
{

}


void TcpServer::setThreadPoolSize(uint16_t num)
{
    threadPool->setThreadNum(num);
}


void TcpServer::start()
{
    threadPool->init();
    tcpAccept->listen();
    isStart=true;
}

void TcpServer::newConnected(int sockfd,const SocketAddr& addr)
{
    base::Log::OUT(base::Log::Info)<<"new tcp connect addr:"<<addr.toString()<<"<cnt>:"<<std::to_string(getConnectCount());

    IOEventLoop* loop = threadPool->getOneLoopFromPool();
    std::shared_ptr<TcpConnect> tcpConnect(new TcpConnect(loop,addr.getAddr(),sockfd));
    addConnect(addr.toString(),tcpConnect);
    tcpConnect->setMessageCallback(std::bind(&TcpServer::messageCallback,this,std::placeholders::_1,std::placeholders::_2));
    tcpConnect->setCloseCallback(std::bind(&TcpServer::connectCloseEvent,this,std::placeholders::_1));
    tcpConnect->connectedHandle();
    connectCallback(tcpConnect);
}

void TcpServer::addConnect(string name,std::shared_ptr<TcpConnect> connect)
{
    connectPool.insert(pair<string,std::shared_ptr<TcpConnect> >(name,connect));
}
void TcpServer::addConnect(string name,TcpConnect* connect)
{
    std::shared_ptr<TcpConnect> connectPtr(connect);
    addConnect(name,connectPtr);
}

void TcpServer::removeConnect(string name)
{
    connectPool.erase(name);
}


void TcpServer::connectCloseEvent(std::shared_ptr<TcpConnect> connect)
{
    connectCloseCallback(connect);
    removeConnect(connect->getName());
}


long TcpServer::getConnectCount()
{
    return connectPool.size();
}

bool TcpServer::haveConect(std::string name)
{
     return (connectPool.find(name) != connectPool.end());
}

void TcpServer::write(TcpConnect& connect,void* data,uint32_t length)
{
    connect.writeInLoop(data,length);
}

void TcpServer::write(std::shared_ptr<TcpConnect> connect,void* data,uint32_t length)
{
    connect->write(data,length);
}


void TcpServer::write(string& name,void* data,uint32_t length)
{
    if(haveConect(name))
    {
        write(connectPool[name],data,length);
    }
    else
    {
        base::Log::OUT(base::Log::Info)<<"try write no exist connect";
    }
}

void TcpServer::write(string& name,string& data)
{
    write(name,&(*data.begin()),data.length());
}
