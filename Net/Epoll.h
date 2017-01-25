#ifndef AGILNET_NET_EPOLL_H
#define AGILNET_NET_EPOLL_H


#include <boost/noncopyable.hpp>

namespace agilNet
{

namespace Net
{


class Epoll : boost::noncopyable
{
public:
    Epoll();
    ~Epoll();
    bool addEvent(int fd,int events);
    bool removeEvent(int fd,int events);
private:
    int epollCtrl(int operation,int fd,int events);
    int epollFd;
};
}
}
#endif
