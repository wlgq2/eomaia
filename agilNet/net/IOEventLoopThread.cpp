#include <net/IOEventLoopThread.h>
#include <iostream>

using namespace agilNet::net;
using namespace std;


IOEventLoopThread::IOEventLoopThread()
    :loop(NULL),
    condtion(mutex)
{

}

IOEventLoop* IOEventLoopThread::getLoopInThread()
{
    {
        MutexGuard lock(mutex);
        //需要阻塞等待线程初始化
        if(NULL == loop)
        {
            //如果线程执行到这里还没有wait，loop被初始化了，并执行类notify，那么这里一直阻塞，所以需要加锁。
            condtion.wait();
        }
    }
    return loop;
}

void IOEventLoopThread::run()
{
    IOEventLoop loop;
    {
        MutexGuard lock(mutex);
        this->loop = &loop;
        condtion.notify();
    }
    loop.run();
}
