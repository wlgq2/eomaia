#include <TcpServer.h>

using namespace agilNet::net;

TcpServer::TcpServer(IOEventLoop* loop)
    :eventLoop(loop),
    isStart(false)
{

}

void TcpServer::start()
{
    isStart.set(true);
}
