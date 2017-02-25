#ifndef AGILNET_SOCKET_OPREATION
#define AGILNET_SOCKET_OPREATION

#include <sys/types.h>
#include <string>
#include <netinet/in.h>

using namespace std;

namespace agilNet
{

namespace net

{
class SocketOperation
{
public:
    static const int32_t Ipv4AddrAny;
    static int bind(int sockfd, const struct sockaddr_in* addr);
    static int createNonblockingSocket();
    static int  listen(int sockfd);
    static int  connect(int sockfd, const struct sockaddr* addr);
    static int  accept(int sockfd, struct sockaddr_in* addr);
    static ssize_t read(int sockfd, void *buf, size_t count);
    static ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt);
    static ssize_t write(int sockfd, const void *buf, size_t count);
    static void close(int sockfd);
    static void getAddrAnyIpv4(struct sockaddr_in& addrIn,uint16_t port);
    static bool toAddrIpv4(const string& addrIp,struct sockaddr_in& addrIn);
    static bool toAddrIpv4(const string& addr,uint16_t port,struct sockaddr_in& addrIn);
    static bool toAddrIpv4(uint16_t port,struct sockaddr_in& addrIn);

    static string ipToString(struct sockaddr_in addr);
    static string toString(struct sockaddr_in addr);

    template<typename T>
    static bool stringToInt(const string& str, T& num);
//private:
};

}
}

#endif // AGILNET_SOCKET_OPREATION
