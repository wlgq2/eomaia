#include <Epoll.h>
#include <sys/epoll.h>


#include <unistd.h>
#include <string.h>

using namespace agilNet::net;

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

bool Epoll::addEvent(IOEvent* ioEvent)
{

    if(epollCtrl(EPOLL_CTL_ADD,ioEvent->getFd(),ioEvent->getEvents())<0)
    {
        return false;
    }
    return true;

}
bool Epoll::removeEvent(IOEvent* ioEvent)
{

    if(epollCtrl(EPOLL_CTL_DEL,ioEvent->getFd(),ioEvent->getEvents())<0)
    {
        return false;
    }
    return true;
}

bool Epoll::modifyEvent(IOEvent* ioEvent)
{
    if(epollCtrl(EPOLL_CTL_MOD,ioEvent->getFd(),ioEvent->getEvents())<0)
    {
        return false;
    }
    return true;
}
