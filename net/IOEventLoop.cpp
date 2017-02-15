#include <IOEventLoop.h>

#include <signal.h>
#include <Log.h>
#include <iostream>
#include <Thread.h>

using namespace std;
using namespace agilNet::log;
using namespace agilNet::net;
using namespace agilNet::thread;
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
    :eventCtrl(new IOEventCtrl(this)),
    thisTheadId(Thread::getNowThreadId())
{

}

IOEventLoop::~IOEventLoop()
{
    delete eventCtrl;
}

void IOEventLoop::run()
{
    if(!inThisThread())
    {
        thisTheadId = Thread::getNowThreadId();
        LogOutput(warning)<<"Loop create and run in different thread";

    }

    while(true)
    {
        eventCtrl->waitAndRunHandle(PollTimeMs);
        runAllFunctionInLoop();
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


void IOEventLoop::runInLoop(boost::function<void ()> func)
{
    if(inThisThread())
    {
        func();
    }
    else
    {
        addFunInLoop(func);
    }

}

void IOEventLoop::addFunInLoop(boost::function<void ()> func)
{
    MutexGuard lock(mutex);
    functions.push_back(func);
}

void IOEventLoop::runAllFunctionInLoop()
{
    MutexGuard lock(mutex);
    for(unsigned int i=0;i<functions.size();i++)
    {
        functions[i]();
    }
    functions.clear();
}
bool IOEventLoop::inThisThread()
{

    return (thisTheadId == Thread::getNowThreadId());
}
