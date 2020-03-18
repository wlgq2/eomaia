#include <base/Thread.h>
#include <chrono>
#include <functional>

using namespace base;

Thread::Thread()
    :started(false),
    thread(new std::thread(std::bind(&Thread::beginRun,this)))

{

}

Thread::~Thread()
{

}

void Thread::start()
{
    std::unique_lock<std::mutex> lock(mutex);
    started = true;
    condtion.notify_one();
}


void Thread::beginRun()
{
    {
        std::unique_lock<std::mutex> lock(mutex);
        //如果在wait函数执行前执行notify则不会有效，所以需要先判断started状态。
        if(!started)
        {
            //如果在这里还未执行wait时，notify被执行，则这里会永远阻塞。所以需要加锁
            condtion.wait(lock);
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
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}


std::thread::id Thread::getNowThreadId()
{
    return std::this_thread::get_id();
}
