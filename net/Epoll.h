#ifndef AGILNET_NET_EPOLL_H
#define AGILNET_NET_EPOLL_H


#include <boost/noncopyable.hpp>
#include <sys/epoll.h>

#include <net/IOEvent.h>

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
    bool removeEvent(int fd);
    int waitEvent(struct epoll_event* eventList,int eventSize,int timeMs);
private:
    int epollCtrl(int operation,int fd,int events);
    int epollFd;
};
}
}
#endif
