#include <net/IOEvent.h>
#include <sys/epoll.h>
#include <unistd.h>

#include <net/IOEventLoop.h>


using namespace agilNet::net;
using namespace boost;

const int IOEvent::noneEventFlag = 0;
const int IOEvent::readEventFlag = EPOLLIN | EPOLLPRI;
const int IOEvent::writeEventFlag = EPOLLOUT;
const int IOEvent::errorEventFlag = EPOLLERR;

IOEvent::IOEvent(IOEventLoop* loop,int fd)
    :eventLoop(loop),
    eventFd(fd),
    events(0)
{

}

IOEvent::~IOEvent()
{
    //::close(eventFd);
}
void IOEvent::enableReading(bool isEnable)
{
    if(isEnable)
        events |= readEventFlag;
    else
        events &= ~readEventFlag;
    update();
}

void IOEvent::enableWriting(bool isEnable)
{
    if(isEnable)
        events |= writeEventFlag;
    else
        events &= ~writeEventFlag;
    update();
}

void IOEvent::enableErrorEvent(bool isEnable)
{
    if(isEnable)
        events |= errorEventFlag;
    else
        events &= ~errorEventFlag;
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
uint32_t IOEvent::getEvents()
{
    return events;
}

void IOEvent::setReadFunc(const function<void()> & func)
{
    readHandle = func;

}
void IOEvent::setWriteFunc(const function<void()> & func)
{
    writeHandle = func;

}
void IOEvent::setErrorFunc(const function<void()> & func)
{
    errorHandle = func;

}
void IOEvent::setCloseFunc(const function<void()> & func)
{
    closeHandle = func;
}
void IOEvent::update()
{
    eventLoop->modifyEvent(eventFd);
}

void IOEvent::removeFromLoop()
{
    eventLoop->removeEvent(eventFd);
}
void IOEvent::handle(uint32_t revents)
{
    if ((revents & EPOLLHUP) && !(revents & EPOLLIN))
    {
        if (closeHandle)
            closeHandle();
    }

    if (revents & EPOLLERR)
    {
        if (errorHandle)
            errorHandle();
    }
    if (revents & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
    {
        if (readHandle)
            readHandle();
    }
    if (revents & EPOLLOUT)
    {
        if (writeHandle)
            writeHandle();
    }
}
