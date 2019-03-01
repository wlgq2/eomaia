#include <net/IOEventLoop.h>

#include <signal.h>
#include <base/LogInterface.h>
#include <base/Thread.h>

#include <iostream>


using namespace std;
using namespace eomaia::net;
using namespace base;


//这个类初始化后避免程序被signal信号意外退出
class IgnoreSigPipe
{
public:
    static IgnoreSigPipe* getInstance ()
    {
        return singnal;
    }
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
    thisTheadId(Thread::getNowThreadId()),
    timerQueue(new TimerQueue(this))
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
        base::Log::OUT( base::Log::Warn)<<"Loop create and run in different thread";

    }

    while(true)
    {
        eventCtrl->waitAndRunHandle(PollTimeMs);
        runAllFunctionInLoop();
    }
}

void IOEventLoop::addEvent(std::shared_ptr<IOEvent> event)
{
    eventCtrl->addEvent(event);
}

void IOEventLoop::removeEvent(std::shared_ptr<IOEvent> event)
{
    eventCtrl->deleteEvent(event);
}

void IOEventLoop::removeEvent(int fd)
{
    eventCtrl->deleteEvent(fd);
}

void IOEventLoop::modifyEvent(std::shared_ptr<IOEvent> event)
{
    eventCtrl->modifyEvent(event);
}

void IOEventLoop::modifyEvent(int fd)
{
    eventCtrl->modifyEvent(fd);
}


void IOEventLoop::runInLoop(const DefaultFunction func)
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

void IOEventLoop::addFunInLoop(DefaultFunction func)
{
    std::lock_guard<std::mutex> lock(mutex);
    functions.push_back(func);
}

void IOEventLoop::runAllFunctionInLoop()
{
    std::lock_guard<std::mutex> lock(mutex);
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

void IOEventLoop::runOniceAfter(const DefaultFunction callback,uint32_t interval)
{
    timerQueue->runOniceAfter(callback,interval);

}

void IOEventLoop::runEveryInterval(const DefaultFunction callback,uint32_t interval)
{
    timerQueue->runEveryInterval(callback,interval);
}
