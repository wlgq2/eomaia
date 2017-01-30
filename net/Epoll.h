#ifndef AGILNET_NET_EPOLL_H
#define AGILNET_NET_EPOLL_H


#include <boost/noncopyable.hpp>
#include <IOEvent.h>


namespace agilNet
{

namespace net
{


class Epoll : boost::noncopyable
{
public:
    Epoll();
    ~Epoll();
    bool addEvent(IOEvent* ioEvent);
    bool removeEvent(IOEvent* ioEvent);
    bool modifyEvent(IOEvent* ioEvent);
private:
    int epollCtrl(int operation,int fd,int events);
    int epollFd;
};
}
}
#endif
