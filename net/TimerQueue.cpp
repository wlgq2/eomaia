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
