#include <TcpAccept.h>

using namespace agilNet::net;

TcpAccept::TcpAccept(IOEventLoop* loop)
    :eventLoop(loop),
    socket(new Socket(SocketOperation::createNonblockingSocket())),
    event(new IOEvent(socket->getFd())),
    listening(false)
{

}

TcpAccept::~TcpAccept()
{

}
