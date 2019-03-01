#include <net/IOEventCtrl.h>

using namespace eomaia::net;
using namespace std;


const int IOEventCtrl::activeEventLength = 16;

IOEventCtrl::IOEventCtrl(IOEventLoop* l)
    :loop(l),
    activeEvents(activeEventLength)
{

}

IOEventCtrl::~IOEventCtrl()
{

    eventPool.clear();
}
void IOEventCtrl::addEvent(std::shared_ptr<IOEvent> event)
{
    eventPool.insert(pair<int,std::weak_ptr<IOEvent> >(event->getFd(),event));
    epoll.addEvent(event.get());
}
void IOEventCtrl::deleteEvent(std::shared_ptr<IOEvent> event)
{
    eventPool.erase(event->getFd());
    epoll.removeEvent(event.get());
}
void IOEventCtrl::modifyEvent(std::shared_ptr<IOEvent> event)
{
    if(eventPool.find(event->getFd()) != eventPool.end())
    {
        eventPool[event->getFd()]=event;
        epoll.modifyEvent(event.get());
    }
}

void  IOEventCtrl::modifyEvent(int fd)
{
    if(eventPool.find(fd) != eventPool.end())
    {
        std::shared_ptr<IOEvent> eventS= eventPool[fd].lock();
        if(eventS)
        {
            IOEvent* event =eventS.get();
            epoll.modifyEvent(event);
        }
    }
}


void IOEventCtrl::deleteEvent(int fd)
{
    if(eventPool.find(fd) != eventPool.end())
    {
        epoll.removeEvent(fd);
        eventPool.erase(fd);
    }
}
void IOEventCtrl::waitAndRunHandle(int timeMs)
{
    int cnt = epoll.waitEvent(&*activeEvents.begin(),activeEvents.size(),timeMs);
    if(cnt<0)
    {
        return ;
    }
    for(int i=0;i<cnt;i++)
    {
        int fd = activeEvents[i].data.fd;
        std::shared_ptr<IOEvent> ioEvent=  eventPool[fd].lock();
        if(ioEvent)
        {
            ioEvent->handle(activeEvents[i].events);
        }
        else
        {
            deleteEvent(fd);
        }
    }
}
