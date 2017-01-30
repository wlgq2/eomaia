#ifndef AGILNET_SOCKET
#define AGILNET_SOCKET

#include <SocketOperation.h>

namespace agilNet
{
namespace net
{

class Socket
{
public:
    Socket(int fd);
    ~Socket();
private:
    int socketFd;
};
}
}

#endif
