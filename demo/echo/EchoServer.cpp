#include <EchoServer.h>
#include <iostream>

EchoServer::EchoServer(IOEventLoop* loop,SocketAddr& addr)
    :TcpServer(loop,addr)
{
}

void EchoServer::connectCallback(int sockfd,const SocketAddr& addr)
{
    cout<<"new connect:"<<endl;
}
void EchoServer::messageCallback()
{
}
void EchoServer::writeCompletCallback()
{
}
