#include "EchoServer.h"
#include <iostream>

#include <base/LogInterface.h>

using namespace eomaia::net;
using namespace std;

EchoServer::EchoServer(IOEventLoop* loop,SocketAddr& addr)
    :TcpServer(loop,addr)
{

}

void EchoServer::connectCallback(std::shared_ptr<TcpConnect> tcpConnect)
{
    cout<<"new connect:"<<tcpConnect->getAddr().toString() <<"<count>" <<getConnectCount()<<endl;
}
void EchoServer::messageCallback(std::shared_ptr<TcpConnect> tcpConnect, Buffer& buffer)
{
    cout<<"thread id:"<<std::this_thread::get_id()<<endl;
    string addr = tcpConnect->getAddr().toString();
    string data;
    buffer.readAllAsString(data);
    cout<<"receive data form "<<addr<<":"<<data<<endl;
    base::Log::OUT(base::Log::Info)<<"receive data form "<<addr<<":"<<data;
    tcpConnect->write(data);
}
void EchoServer::writeCompletCallback(std::shared_ptr<TcpConnect> tcpConnect)
{
    cout<<"thread id:"<<std::this_thread::get_id()<<endl;
    string addr = tcpConnect->getAddr().toString();
    cout<<addr<<":"<<"write complet "<<endl;
    base::Log::OUT(base::Log::Info)<<addr<<":"<<"write complet ";
}

void EchoServer::connectCloseCallback( std::shared_ptr<TcpConnect> connect)
{
    string addr = connect->getAddr().toString();
    cout<<"close connect :"<<addr<<endl;
    base::Log::OUT(base::Log::Info)<<"close connect : "<<addr;
}
