#ifndef AGILNET_NET_TIMER_QUEUE
#define AGILNET_NET_TIMER_QUEUE

#include <map>
#include <Timer.h>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <IOEvent.h>
#include <Mutex.h>

namespace agilNet
{

namespace net
{
class IOEventLoop;

class TimerQueue
{
public:
    TimerQueue(IOEventLoop* eventLoop);
    ~TimerQueue();
    void addOniceTimer(uint32_t interval,boost::function<void ()>* handle);
    void runOniceAfter(int interval,boost::function<void ()>* handle);

private:
    IOEventLoop* loop;
    int timerFd;
    boost::shared_ptr<IOEvent> event;
    Mutex mutex;
    std::multimap<uint64_t,boost::shared_ptr<Timer> > everytimers;
    std::multimap<uint64_t,boost::shared_ptr<Timer> > oniceTimers;

    int createTimeFd();
    void timerHandle();
};

}
}

#endif // AGILNET_NET_TIME_QUEUE
