#include <SocketOperation.h>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <sstream>

using namespace agilNet::net;

int SocketOperation::createNonblockingSocket()
{
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (sockfd < 0)
    {

    }
    return sockfd;

}
int  SocketOperation::connect(int sockfd, const struct sockaddr* addr)
{
    return ::connect(sockfd, addr, static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
}
int  SocketOperation::accept(int sockfd, struct sockaddr_in6* addr)
{

}
ssize_t SocketOperation::read(int sockfd, void *buf, size_t count)
{
    return ::read(sockfd, buf, count);
}
ssize_t SocketOperation::readv(int sockfd, const struct iovec *iov, int iovcnt)
{
    return ::readv(sockfd, iov, iovcnt);
}
ssize_t SocketOperation::write(int sockfd, const void *buf, size_t count)
{
    return ::write(sockfd, buf, count);
}
void SocketOperation::close(int sockfd)
{
    if (::close(sockfd) < 0)
    {

    }
}
bool SocketOperation::toAddrIpv4(const string& addrIp,struct sockaddr_in& addrIn)
{
    vector<string> strs;
    boost::split(strs, addrIp, boost::is_any_of(":"));
    if(strs.size()!=2)
    {
        return false;
    }

    uint16_t port;
    if(!stringToInt<uint16_t>(strs[1],port))
    {
        return false;
    }
    return toAddrIpv4(strs[0],port,addrIn);
}
bool SocketOperation::toAddrIpv4(const string& addr,int port,struct sockaddr_in& addrIn)
{
    vector<string> ip;
    boost::split(ip, addr, boost::is_any_of("."));
    if(ip.size()!=4)
    {
        return false;
    }
    uint16_t addrArray[4];
    for(int i=0;i<4;i++)
    {

        if(!stringToInt<uint16_t>(ip[i],addrArray[i]))
        {
            return false;
        }
        if(addrArray[i]>255)
        {
            return false;
        }
    }
    uint32_t addr32 ;
    for(int i=0;i<4;i++)
    {
        addr32 <<= 8;
        addr32 |= addrArray[i];
    }
    bzero(&addrIn, sizeof(addrIn));
    addrIn.sin_family = AF_INET;
    addrIn.sin_port = htons(port);
    addrIn.sin_addr.s_addr = addr32;
    return true;
}

bool SocketOperation::toAddrIpv4(int port,struct sockaddr_in& addrIn)
{
    bzero(&addrIn, sizeof(addrIn));
    addrIn.sin_family = AF_INET;
    addrIn.sin_port = htons(port);
    addrIn.sin_addr.s_addr = htonl (INADDR_ANY);
    return true;
}
string SocketOperation::ipToString(struct sockaddr_in addr)
{
    string sAddr ;
    return sAddr;
}
string SocketOperation::toString(struct sockaddr_in addr)
{
    string addrPort ;
    addrPort = ipToString(addr);
    return addrPort;
}
template<typename T>
bool SocketOperation::stringToInt(const string& str, T& num)
{
    std::stringstream stream;
    stream<< str<<endl;
    stream>>num;
    return stream.good();
}
