#include <Thread.h>

using namespace agilNet::thread;
using namespace agilNet;

Thread::Thread()
    :started(false),
    condtion(mutex),
    thread(new boost::thread(boost::bind(&Thread::beginRun,this)))

{

}

Thread::~Thread()
{

}

void Thread::start()
{
    started = true;
    condtion.notify();
}


void Thread::beginRun()
{
    if(!started)
    {
        //如果在wait函数执行前执行notify则不会有效，所以需要先判断started状态。
        condtion.wait();
    }
    run();
}

long long Thread::getThreadPtrId()
{
    if(NULL == thread.get())
    {
        return -1;
    }
    else
    {
        return (long long)(thread.get());
    }
}

bool Thread::isStarted()
{
    return started;
}

void Thread::sleepSeconds(int seconds)
{
    boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}
