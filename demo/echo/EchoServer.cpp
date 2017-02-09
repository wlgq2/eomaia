#include <EchoServer.h>
#include <iostream>

using namespace agilNet::net;
using namespace std;

EchoServer::EchoServer(IOEventLoop* loop,SocketAddr& addr)
    :TcpServer(loop,addr)
{
}

void EchoServer::connectCallback(int sockfd,const SocketAddr& addr)
{
    cout<<"new connect:"<<addr.toString()<<endl;
}
void EchoServer::messageCallback()
{
}
void EchoServer::writeCompletCallback()
{
}
