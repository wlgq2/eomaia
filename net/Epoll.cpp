#include <net/Epoll.h>
#include <support/Log.h>
#include <string.h>
#include <unistd.h>

using namespace agilNet::net;
using namespace agilNet::log;

Epoll::Epoll()
    :epollFd(epoll_create1(EPOLL_CLOEXEC))
{
    if(epollFd<0)
    {
        Log::getSingle()->write(Log::error,"create epoll error.");
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
        Log::getSingle()->write(Log::error,"add epoll error.");
        return false;
    }
    return true;

}
bool Epoll::removeEvent(IOEvent* ioEvent)
{

    if(epollCtrl(EPOLL_CTL_DEL,ioEvent->getFd(),ioEvent->getEvents())<0)
    {
        Log::getSingle()->write(Log::error,"delete epoll error.");
        return false;
    }
    return true;
}

bool Epoll::removeEvent(int fd)
{

    if(epollCtrl(EPOLL_CTL_DEL,fd,0)<0)
    {
        Log::getSingle()->write(Log::error,"delete epoll error.");
        return false;
    }
    return true;
}
bool Epoll::modifyEvent(IOEvent* ioEvent)
{
    if(epollCtrl(EPOLL_CTL_MOD,ioEvent->getFd(),ioEvent->getEvents())<0)
    {
        Log::getSingle()->write(Log::error,"modify epoll error.");
        return false;
    }
    return true;
}

int Epoll::waitEvent(struct epoll_event* eventList,int eventSize,int timeMs)
{
    int rst = epoll_wait(epollFd, eventList, eventSize, timeMs);
    return rst ;
}
