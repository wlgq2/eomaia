#include <IOEventLoop.h>

#include <signal.h>
#include <Log.h>
#include <iostream>

using namespace std;
using namespace agilNet::log;
using namespace agilNet::net;
using namespace boost;

//这个类初始化后避免程序被signal信号意外退出
class IgnoreSigPipe
{
private:
    IgnoreSigPipe()
    {
        ::signal(SIGPIPE, SIG_IGN);
        //endl;
    }
    static IgnoreSigPipe* singnal ;
};

IgnoreSigPipe* IgnoreSigPipe::singnal = new IgnoreSigPipe();



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
