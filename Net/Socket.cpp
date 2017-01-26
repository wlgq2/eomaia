#include <Socket.h>
#include <SocketOperation.h>

using namespace agilNet::net;

Socket::Socket(int fd)
    :socketFd(fd)
{

}

Socket::~Socket()
{
    SocketOperation::close(socketFd);
}
