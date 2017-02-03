#include <IOEvent.h>
#include <sys/epoll.h>
#include <unistd.h>

#include <IOEventLoop.h>

using namespace agilNet::net;

const int IOEvent::noneEventFlag = 0;
const int IOEvent::readEventFlag = EPOLLIN | EPOLLPRI;
const int IOEvent::writeEventFlag = EPOLLOUT;

IOEvent::IOEvent(int fd)
    :eventFd(fd),
    events(0)
{
}

IOEvent::~IOEvent()
{
    //::close(eventFd);
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
uint32_t IOEvent::getEvents()
{
    return events;
}

void IOEvent::setReadFunc(function<void()> func)
{
    readHandle = func;

}
void IOEvent::setWriteFunc(function<void()> func)
{
    writeHandle = func;

}
void IOEvent::setErrorFunc(function<void()> func)
{
    errorHandle = func;

}
void IOEvent::setCloseFunc(function<void()> func)
{
    closeHandle = func;
}
void IOEvent::update()
{

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
