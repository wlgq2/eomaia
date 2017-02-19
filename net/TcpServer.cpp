#include <net/TcpServer.h>
#include <boost/thread/thread.hpp>
#include <support/Log.h>


using namespace agilNet::log;
using namespace agilNet::net;
using namespace std;
using namespace boost;


TcpServer::TcpServer(IOEventLoop* loop,SocketAddr& addr)
    :eventLoop(loop),
    tcpAddr(addr),
    tcpAccept(new TcpAccept(loop,addr)),
    isStart(false),
    threadPool(new IOEventLoopThreadPool(loop))
{
    tcpAccept->setNewConnectCallback(boost::bind(&TcpServer::newConnected,this,_1,_2));
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
    isStart.set(true);
}

void TcpServer::newConnected(int sockfd,const SocketAddr& addr)
{
    LogOutput(info)<<"new tcp connect addr:"<<addr.toString()<<"<cnt>:"<<getConnectCount();

    IOEventLoop* loop = threadPool->getOneLoopFromPool();
    shared_ptr<TcpConnect> tcpConnect(new TcpConnect(loop,addr.getAddr(),sockfd));
    addConnect(addr.toString(),tcpConnect);
    tcpConnect->setMessageCallback(boost::bind(&TcpServer::messageCallback,this,_1,_2));
    tcpConnect->setCloseCallback(boost::bind(&TcpServer::connectCloseEvent,this,_1));
    tcpConnect->connectedHandle();
    connectCallback(tcpConnect);
}

void TcpServer::addConnect(string name,shared_ptr<TcpConnect> connect)
{
    connectPool.insert(pair<string,shared_ptr<TcpConnect> >(name,connect));
}
void TcpServer::addConnect(string name,TcpConnect* connect)
{
    shared_ptr<TcpConnect> connectPtr(connect);
    addConnect(name,connectPtr);
}

void TcpServer::removeConnect(string name)
{
    connectPool.erase(name);
}


void TcpServer::connectCloseEvent(boost::shared_ptr<TcpConnect> connect)
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

void TcpServer::write(shared_ptr<TcpConnect> connect,void* data,uint32_t length)
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
        LogOutput(info)<<"try write no exist connect";
    }
}

void TcpServer::write(string& name,string& data)
{
    write(name,&(*data.begin()),data.length());
}
