#include <TcpServer.h>
#include <boost/thread/thread.hpp>
#include <Log.h>


using namespace agilNet::support;
using namespace agilNet::net;
using namespace std;
using namespace boost;


TcpServer::TcpServer(IOEventLoop* loop,SocketAddr& addr)
    :eventLoop(loop),
    tcpAddr(addr),
    tcpAccept(new TcpAccept(loop,addr)),
    isStart(false)
{
    tcpAccept->setNewConnectCallback(boost::bind(&TcpServer::newConnected,this,_1,_2));

}


TcpServer::~TcpServer()
{

}

void TcpServer::start()
{
    tcpAccept->listen();
    isStart.set(true);
}

void TcpServer::newConnected(int sockfd,const SocketAddr& addr)
{
    LogOutput(info)<<"new tcp connect addr:"<<addr.toString();

    shared_ptr<TcpConnect> tcpConnect(new TcpConnect(eventLoop,addr.getAddr(),sockfd));
    addConnect(addr.toString(),tcpConnect);
    tcpConnect->setMessageCallback(boost::bind(&TcpServer::messageCallback,this,_1,_2));

    connectCallback(sockfd,addr);
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
