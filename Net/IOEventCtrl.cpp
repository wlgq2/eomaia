#include <IOEventCtrl.h>

using namespace agilNet::net;

IOEventCtrl::IOEventCtrl(IOEventLoop* l)
    :loop(l)
{

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

void IOEventCtrl::waitAndRunHandle()
{

}
