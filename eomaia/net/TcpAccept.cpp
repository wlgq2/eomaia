#include <net/TcpAccept.h>
#include <thread>

#include <unistd.h>

using namespace eomaia::net;

TcpAccept::TcpAccept(IOEventLoop* loop,SocketAddr& addr)
    :eventLoop(loop),
    socket(new Socket(SocketOperation::createNonblockingSocket())),
    event(new IOEvent(loop,socket->getFd())),
    listening(false)
{
    loop->addEvent(event);
    socket->bind(addr);
    event->setReadFunc(std::bind(&TcpAccept::acceptHandle,this));
}

TcpAccept::~TcpAccept()
{

    event->disableAll();
    event->removeFromLoop();
}


void TcpAccept::listen()
{
    socket->listen();
    event->enableReading(true);
}
bool TcpAccept:: isListen()
{
    return listening;
}
void  TcpAccept::setNewConnectCallback( const NewConnectCallback callback)
{
    newConnectCallback = callback;
}

void TcpAccept:: acceptHandle()
{
    SocketAddr connectAddr;
    int fd;
    if((fd =socket->accept(connectAddr))>0)
    {
        if(newConnectCallback)
        {
            newConnectCallback(fd,connectAddr);
        }
        else
        {
            ::close(fd);
        }
    }
}
