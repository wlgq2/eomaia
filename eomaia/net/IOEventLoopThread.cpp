#include <net/IOEventLoopThread.h>
#include <iostream>

using namespace eomaia::net;
using namespace std;


IOEventLoopThread::IOEventLoopThread()
    :loop(nullptr)
{

}

IOEventLoop* IOEventLoopThread::getLoopInThread()
{
    {
        std::unique_lock<std::mutex> lock(mutex);
        //需要阻塞等待线程初始化
        if(nullptr == loop)
        {
            //如果线程执行到这里还没有wait，loop被初始化了，并执行类notify，那么这里一直阻塞，所以需要加锁。
            condtion.wait(lock);
        }
    }
    return loop;
}

void IOEventLoopThread::run()
{
    IOEventLoop loop;
    {
        std::unique_lock<std::mutex> lock(mutex);
        this->loop = &loop;
        condtion.notify_one();
    }
    loop.run();
}
