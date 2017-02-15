#include <Timer.h>

using namespace agilNet::net;
using namespace boost;

Timer::Timer(uint32_t interval,function<void ()>* funcHandle)
    :intervalMs(interval),
    handle(funcHandle)
{
    struct  timezone   tz;
    gettimeofday(&now,&tz);
}


struct timeval Timer::getTimeOut()
{
    struct timeval timeOut = now;
    timeOut.tv_sec +=intervalMs/1000;
    timeOut.tv_usec += (intervalMs%1000)*1000;
    return timeOut;
}

struct timespec Timer::getTimeInterval()
{
    struct timespec timerInterval ;
    timerInterval.tv_sec =intervalMs/1000;
    timerInterval.tv_nsec = (intervalMs%1000)*1000000;
    return timerInterval;
}


void Timer::update()
{
    struct  timezone   tz;
    gettimeofday(&now,&tz);
}

uint64_t Timer::getTimeOutMSencond()
{
    struct timeval timeOut = getTimeOut();
    int mSecond = timeOut.tv_sec *1000 + timeOut.tv_usec/1000;
    return mSecond;
}

void Timer::setHandle(shared_ptr<function<void ()> > func)
{
    handle = func;
}
