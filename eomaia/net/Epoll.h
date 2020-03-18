#ifndef EOMAIA_NET_EPOLL_H
#define EOMAIA_NET_EPOLL_H


#include <sys/epoll.h>

#include <net/IOEvent.h>

namespace eomaia
{

namespace net
{


class Epoll
{
public:
    Epoll( const Epoll& ) = delete;
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
