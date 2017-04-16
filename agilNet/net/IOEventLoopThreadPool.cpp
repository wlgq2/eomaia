#include <net/IOEventLoopThreadPool.h>

using namespace agilNet::net;
using namespace boost;

IOEventLoopThreadPool::IOEventLoopThreadPool(IOEventLoop* loop)
    :mainLoop(loop),
    started(false),
    threadNum(0),
    threadIndex(0)
{
}


void IOEventLoopThreadPool::init()
{
    for(int i=0;i<threadNum;i++)
    {
        shared_ptr<IOEventLoopThread> thread(new IOEventLoopThread());
        thread->start();
        threadPool.push_back(thread);
        eventLoopPool.push_back(thread->getLoopInThread());
    }
    started = true;
}

void IOEventLoopThreadPool::init(int num)
{
    setThreadNum(num);
    init();
}

bool IOEventLoopThreadPool::isStarted()
{
    return started;
}

void IOEventLoopThreadPool::setThreadNum(uint16_t num)
{
    threadNum = num;
}


IOEventLoop* IOEventLoopThreadPool::getOneLoopFromPool()
{
    //如果线程池为空则返回主Loop
    if(eventLoopPool.empty())
        return mainLoop;

    threadIndex++;
    if(threadIndex>=eventLoopPool.size())
        threadIndex = 0;
    return eventLoopPool[threadIndex];
}

IOEventLoop* IOEventLoopThreadPool::getOneLoopFromPoolWithHash(int hashCode)
{
    //如果线程池为空则返回主Loop
    if(eventLoopPool.empty())
        return mainLoop;

    uint16_t index = hashCode%eventLoopPool.size();
    return eventLoopPool[index];

}
