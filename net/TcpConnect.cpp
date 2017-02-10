#include <TcpConnect.h>
#include <boost/thread/thread.hpp>
#include <Log.h>
#include <iostream>


using namespace agilNet::log;
using namespace agilNet::net;
using namespace std;


TcpConnect::TcpConnect(IOEventLoop* l,struct sockaddr_in addr,int fd)
    :loop(l),
    socketAddr(addr),
    name(socketAddr.toString()),
    socket(new Socket(fd)),
    event(new IOEvent(loop,fd))
{
    loop->addEvent(event);
    event->enableReading(true);
    event->enableErrorEvent(true);
    event->setReadFunc(boost::bind(&TcpConnect::readEvent,this));
    event->setCloseFunc(boost::bind(&TcpConnect::closeEvent,this));
}

TcpConnect::~TcpConnect()
{
    event->disableAll();
    event->removeFromLoop();
    loop->removeEvent(event);
}


void TcpConnect::setMessageCallback(boost::function<void (const TcpConnect&, Buffer&)> callback)
{
    messageCallback = callback;
}

void TcpConnect::setCloseCallback(boost::function<void (const TcpConnect&)> callback)
{
    closeCallback = callback;
}

void TcpConnect::readEvent()
{

    int error= 0;
    int n = readBuf.readFromIO(event->getFd(), error);
    if (n > 0)
    {
        if(messageCallback)
            messageCallback(getRefer(),readBuf);
    }
    else if (n == 0)
    {
        closeEvent();
    }
    else
    {
        LogOutput(error) << "TcpConnection::handleRead error :"<<error;
        //handleError();
    }
}

void TcpConnect::closeEvent()
{
    if(closeCallback)
        closeCallback(getRefer());
}

const TcpConnect& TcpConnect::getRefer()
{
    return (*this);
}

const SocketAddr& TcpConnect::getAddr() const
{
    return socketAddr;
}

string TcpConnect::getName() const
{
    return name;
}
