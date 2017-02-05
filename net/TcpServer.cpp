#include <TcpServer.h>
#include <boost/thread/thread.hpp>

using namespace agilNet::net;

TcpServer::TcpServer(IOEventLoop* loop,SocketAddr& addr)
    :eventLoop(loop),
    tcpAddr(addr),
    tcpAccept(new TcpAccept(loop,addr)),
    isStart(false)
{
    tcpAccept->setNewConnectCallback(boost::bind(&TcpServer::connectCallback,this,_1,_2));
}

void TcpServer::start()
{
    tcpAccept->listen();
    isStart.set(true);
}

