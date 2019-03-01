#ifndef EOMAIA_SOCKET
#define EOMAIA_SOCKET

#include <net/SocketOperation.h>
#include <net/SocketAddr.h>

namespace eomaia
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
    void setTcpNoDelay(bool enable);
    int shutdownWrite();
private:
    int socketFd;
};
}
}

#endif
