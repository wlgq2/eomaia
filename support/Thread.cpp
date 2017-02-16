#include <support/Thread.h>

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
    {
        MutexGuard mutexGuard(mutex);
        started = true;
        condtion.notify();
    }
}


void Thread::beginRun()
{
    {
        MutexGuard mutexGuard(mutex);
        //如果在wait函数执行前执行notify则不会有效，所以需要先判断started状态。
        if(!started)
        {
            //如果在这里还未执行wait时，notify被执行，则这里会永远阻塞。所以需要加锁
            condtion.wait();
        }
    }
    run();
}


bool Thread::isStarted()
{
    return started;
}

void Thread::sleepSeconds(int seconds)
{
    boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}


boost::thread::id Thread::getNowThreadId()
{
    return boost::this_thread::get_id();
}
