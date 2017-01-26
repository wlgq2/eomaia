#include <IOEvent.h>
#include <sys/epoll.h>


using namespace agilNet::net;

const int IOEvent::noneEventFlag = 0;
const int IOEvent::readEventFlag = EPOLLIN | EPOLLPRI;
const int IOEvent::writeEventFlag = EPOLLOUT;

IOEvent::IOEvent(int fd)
    :eventFd(fd),
    events(0)
{

}

void IOEvent::enableReading()
{
    events |= readEventFlag;
    update();
}
void IOEvent::disableReading()
{
    events &= ~readEventFlag;
    update();
}
void IOEvent::enableWriting()
{
    events |= writeEventFlag;
    update();
}
void IOEvent::disableWriting()
{
    events &= ~writeEventFlag;
    update();
}
void IOEvent::disableAll()
{
    events = noneEventFlag;
    update();
}
bool IOEvent::isWriting()
{
    return events & writeEventFlag;
}
bool IOEvent::isReading()
{
    return events & writeEventFlag;
}
int IOEvent::getFd()
{
    return eventFd;

}
int IOEvent::getEvents()
{
    return events;
}

void IOEvent::update()
{

}

void IOEvent::handle()
{

}
