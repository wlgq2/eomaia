#include <TimerQueue.h>

#include <IOEventLoop.h>
#include <sys/timerfd.h>
#include <Log.h>

using namespace agilNet::net;
using namespace boost;
using namespace std;


TimerQueue::TimerQueue(IOEventLoop* eventLoop)
    :loop(eventLoop),
    timerFd(createTimeFd()),
    event(new IOEvent(loop,timerFd))
{

    loop->addEvent(event);
    event->enableReading(true);
    event->setReadFunc(bind(&TimerQueue::timerHandle,this));
}


TimerQueue::~TimerQueue()
{
    ::close(timerFd);
}


void TimerQueue::runOniceAfter(int interval,function<void ()>* handle)
{
    MutexGuard lock(mutex);
    addOniceTimer(interval,handle);
}

void TimerQueue::addOniceTimer(uint32_t interval,function<void ()>* handle)
{
    shared_ptr<Timer> timer(new Timer(interval,handle));
    oniceTimers.insert(pair<uint64_t,shared_ptr<Timer> >(timer->getTimeOutMSencond(),timer));
    if(needResetTimer(oniceTimers,timer))
    {
        resetTimer(timer);
    }
}

void TimerQueue::resetTimer(shared_ptr<Timer> timer)
{
    struct itimerspec newValue;
    struct itimerspec oldValue;
    bzero(&newValue, sizeof newValue);
    bzero(&oldValue, sizeof oldValue);
    newValue.it_value = timer->getTimeInterval();
    int ret = ::timerfd_settime(timerFd, 0, &newValue, &oldValue);
    if (ret<0)
    {
        LogOutput(error) << "timerfd_settime() error";
    }
}

int TimerQueue::createTimeFd()
{
  int fd = ::timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK | TFD_CLOEXEC);
  if (fd < 0)
  {
    LogOutput(error) << "failed to create time fd";
  }
  return fd;
}

void TimerQueue::timerHandle()
{
    MutexGuard lock(mutex);
}

bool TimerQueue::needResetTimer(multimap<uint64_t,shared_ptr<Timer> > times , shared_ptr<Timer> timer)
{
    multimap<uint64_t,shared_ptr<Timer> >::iterator it = times.begin();
    //如果触发时间小于新增定时器时间，则不需要重置定时器。
    if(it->first < timer->getTimeOutMSencond())
    {
        return false;
    }
    //如果键值已存在，则不需要重置定时器
    if(times.count( timer->getTimeOutMSencond())>1)
    {
        return false;
    }
    return true;
}
