#include <IOEventLoop.h>


using namespace agilNet::net;

const int IOEventLoop::PollTimeMs = 3000;
IOEventLoop::IOEventLoop()
    :eventCtrl(new IOEventCtrl(this))
{

}

IOEventLoop::~IOEventLoop()
{
    delete eventCtrl;
}
void IOEventLoop::run()
{
    while(true)
    {
        eventCtrl->waitAndRunHandle(PollTimeMs);
    }
}

void IOEventLoop::addEvent(shared_ptr<IOEvent> event)
{
    eventCtrl->addEvent(event);
}
void IOEventLoop::removeEvent(shared_ptr<IOEvent> event)
{
    eventCtrl->deleteEvent(event);
}
void IOEventLoop::removeEvent(int fd)
{
    eventCtrl->deleteEvent(fd);
}
void IOEventLoop::modifyEvent(shared_ptr<IOEvent> event)
{
    eventCtrl->modifyEvent(event);
}

void IOEventLoop::modifyEvent(int fd)
{
    eventCtrl->modifyEvent(fd);
}
