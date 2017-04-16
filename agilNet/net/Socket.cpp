#include <net/Socket.h>
#include <net/SocketOperation.h>


using namespace agilNet::net;

Socket::Socket(int fd)
    :socketFd(fd)
{

}

Socket::~Socket()
{
    SocketOperation::close(socketFd);
}
int Socket::getFd()
{
    return socketFd;
}
void Socket::bind(SocketAddr& addr)
{
    SocketOperation::bind(socketFd,addr.getAddrPtr());
}
int Socket::accept(SocketAddr& addr)
{
    struct sockaddr_in  clientAddr;
    int rst = SocketOperation::accept(socketFd,&clientAddr);
    if(rst>0)
    {
        addr.setAddr(clientAddr);
    }
    return rst;
}
void Socket::listen()
{
    SocketOperation::listen(socketFd);
}

void Socket::setTcpNoDelay(bool enable)
{
    SocketOperation::setTcpNoDelay(socketFd,enable);
}

int Socket::shutdownWrite()
{
    return SocketOperation::shutdownWrite(socketFd);
}
