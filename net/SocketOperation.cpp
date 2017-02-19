#include <net/SocketOperation.h>

#include <boost/algorithm/string.hpp>
#include <vector>
#include <sstream>
#include <support/Log.h>

using namespace agilNet::log;
using namespace agilNet::net;
using namespace std;

const int32_t SocketOperation::Ipv4AddrAny =htonl (INADDR_ANY);


int SocketOperation::createNonblockingSocket()
{
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (sockfd < 0)
    {
        Log::getSingle()->write(Log::error,"create socket error.");
    }
    return sockfd;

}

int SocketOperation::bind(int sockfd, const struct sockaddr_in* addr)
{
    int ret = ::bind(sockfd,  (struct sockaddr *)addr, (sizeof(struct sockaddr)));
    if (ret < 0)
    {
        Log::getSingle()->write(Log::error,"bind socket error.");
    }
    return ret;
}

int SocketOperation::listen(int sockfd)
{
    int ret = ::listen(sockfd, SOMAXCONN);
    if (ret < 0)
    {
        Log::getSingle()->write(Log::error,"listen socket error.");
    }
    return ret;
}
int  SocketOperation::connect(int sockfd, const struct sockaddr* addr)
{
    return ::connect(sockfd, addr, static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
}
int  SocketOperation::accept(int sockfd, struct sockaddr_in* addr)
{
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int ret = ::accept(sockfd, (struct sockaddr *)addr,&addrlen);
    if(ret<0)
    {
        Log::getSingle()->write(Log::error,"accept socket error.");
    }
    return ret;
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
        Log::getSingle()->write(Log::error,"close socket error.");
    }
}
void SocketOperation::getAddrAnyIpv4(struct sockaddr_in& addrIn,uint16_t port)
{
    bzero(&addrIn, sizeof(addrIn));
    addrIn.sin_family = AF_INET;
    addrIn.sin_port = htons(port);
    addrIn.sin_addr.s_addr = Ipv4AddrAny;
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
bool SocketOperation::toAddrIpv4(const string& addr,uint16_t port,struct sockaddr_in& addrIn)
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

bool SocketOperation::toAddrIpv4(uint16_t port,struct sockaddr_in& addrIn)
{
    bzero(&addrIn, sizeof(addrIn));
    addrIn.sin_family = AF_INET;
    addrIn.sin_port = htons(port);
    addrIn.sin_addr.s_addr = htonl (INADDR_ANY);
    return true;
}

string SocketOperation::ipToString(struct sockaddr_in addr)
{
    std::stringstream stream;

    uint8_t* addrArray= (uint8_t*)&addr.sin_addr.s_addr;
    for(int i=0;i<4;i++)
    {
        stream<<(uint16_t)addrArray[i];
        if(i!=3)
           stream <<".";
    }
    stream<<":"<<(((addr.sin_port<<8)&0x00ffff)|(addr.sin_port>>8));
    return stream.str() ;
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


int SocketOperation::shutdownWrite(int sockfd)
{
    int rst ;
    if ((rst = ::shutdown(sockfd, SHUT_WR)) < 0)
    {
        LogOutput(error) << "shutdown write  error";
    }
    return rst;
}

void SocketOperation::setTcpNoDelay(int fd,bool isEnable)
{
    int opt = isEnable? 1:0;
    ::setsockopt(fd,IPPROTO_TCP,TCP_NODELAY,&opt,sizeof(opt));
}
