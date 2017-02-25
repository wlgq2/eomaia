#ifndef AGILNET_SOCKET
#define AGILNET_SOCKET

#include <SocketOperation.h>
#include <SocketAddr.h>

namespace agilNet
{
namespace net
{

class Socket
{
public:
    Socket(int fd);
    ~Socket();
    void bind(SocketAddr& addr);
    int accept(SocketAddr& addr);
    void listen();
    int getFd();
private:
    int socketFd;
};
}
}

#endif
