#include "EchoServer.h"
#include <iostream>

#include <support/Log.h>

using namespace agilNet::log;
using namespace agilNet::net;
using namespace std;
using namespace boost;

EchoServer::EchoServer(IOEventLoop* loop,SocketAddr& addr)
    :TcpServer(loop,addr)
{

}

void EchoServer::connectCallback(shared_ptr<TcpConnect> tcpConnect)
{
    cout<<"new connect:"<<tcpConnect->getAddr().toString() <<"<count>" <<getConnectCount()<<endl;
}
void EchoServer::messageCallback(shared_ptr<TcpConnect> tcpConnect, Buffer& buffer)
{
    cout<<"thread id:"<<boost::this_thread::get_id()<<endl;
    string addr = tcpConnect->getAddr().toString();
    string data;
    buffer.readAllAsString(data);
    cout<<"receive data form "<<addr<<":"<<data<<endl;
    LogOutput(info)<<"receive data form "<<addr<<":"<<data;
    tcpConnect->write(data);
}
void EchoServer::writeCompletCallback(boost::shared_ptr<TcpConnect> tcpConnect)
{
    cout<<"thread id:"<<boost::this_thread::get_id()<<endl;
    string addr = tcpConnect->getAddr().toString();
    cout<<addr<<":"<<"write complet "<<endl;
    LogOutput(info)<<addr<<":"<<"write complet "<<endl;
}

void EchoServer::connectCloseCallback( boost::shared_ptr<TcpConnect> connect)
{
    string addr = connect->getAddr().toString();
    cout<<"close connect :"<<addr<<endl;
    LogOutput(info)<<"close connect : "<<addr;
}
