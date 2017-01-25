#include <Epoll.h>
#include <sys/epoll.h>


#include <unistd.h>
#include <string.h>

using namespace agilNet::Net;

Epoll::Epoll():
    epollFd(epoll_create1(EPOLL_CLOEXEC))
{
    if(epollFd<0)
    {


    }
}

Epoll::~Epoll()
{

    ::close(epollFd);
}


int Epoll::epollCtrl(int operation,int fd,int events)
{
    struct epoll_event event;
    bzero(&event, sizeof event);
    event.events = events;
    event.data.fd = fd;
    int rst = epoll_ctl(epollFd, operation, fd, &event);
    return rst;

}

bool Epoll::addEvent(int fd,int events)
{

    if(epollCtrl(EPOLL_CTL_ADD,fd,events)<0)
    {
        return false;
    }
    return true;

}
bool Epoll::removeEvent(int fd,int events)
{

    if(epollCtrl(EPOLL_CTL_DEL,fd,events)<0)
    {
        return false;
    }
    return true;
}

