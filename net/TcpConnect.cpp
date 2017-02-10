#include <TcpConnect.h>
#include <boost/thread/thread.hpp>
#include <Log.h>


using namespace agilNet::support;
using namespace agilNet::net;


TcpConnect::TcpConnect(IOEventLoop* l,struct sockaddr_in addr,int fd)
    :loop(l),
    socketAddr(addr),
    socket(new Socket(fd)),
    event(new IOEvent(loop,fd))
{
    loop->addEvent(event);
    event->enableReading(true);
    event->setReadFunc(boost::bind(&TcpConnect::readFunction,this));
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

void TcpConnect::readFunction()
{

    int error= 0;
    int n = readBuf.readFromIO(event->getFd(), error);
    if (n > 0)
    {
        messageCallback(getRefer(),readBuf);
    }
    else if (n == 0)
    {
        //handleClose();
    }
    else
    {
        LogOutput(error) << "TcpConnection::handleRead error :"<<error;
        //handleError();
    }
}


const TcpConnect& TcpConnect::getRefer()
{
    return (*this);
}

const SocketAddr& TcpConnect::getAddr() const
{
    return socketAddr;
}
