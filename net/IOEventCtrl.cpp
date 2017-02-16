#include <net/IOEventCtrl.h>

using namespace agilNet::net;
using namespace std;
using namespace boost;

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
void IOEventCtrl::addEvent(shared_ptr<IOEvent> event)
{
    eventPool.insert(pair<int,weak_ptr<IOEvent> >(event->getFd(),event));
    epoll.addEvent(event.get());
}
void IOEventCtrl::deleteEvent(shared_ptr<IOEvent> event)
{
    eventPool.erase(event->getFd());
    epoll.removeEvent(event.get());
}
void IOEventCtrl::modifyEvent(shared_ptr<IOEvent> event)
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
        shared_ptr<IOEvent> eventS= eventPool[fd].lock();
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
        shared_ptr<IOEvent> ioEvent=  eventPool[fd].lock();
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
