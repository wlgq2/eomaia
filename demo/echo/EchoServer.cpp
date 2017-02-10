#include <EchoServer.h>
#include <iostream>

#include <Log.h>

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
void EchoServer::messageCallback(const TcpConnect& tcpConnect, Buffer& buffer)
{
    string addr = tcpConnect.getAddr().toString();
    string data = buffer.readAllAsString();
    cout<<"receive data form "<<addr<<":"<<data<<endl;
    LogOutput(info)<<"receive data form "<<addr<<":"<<data<<endl;
}
void EchoServer::writeCompletCallback()
{
}
