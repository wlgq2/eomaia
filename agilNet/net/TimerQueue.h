#ifndef AGILNET_NET_TIMER_QUEUE
#define AGILNET_NET_TIMER_QUEUE

#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <net/IOEvent.h>
#include <net/Timer.h>

#include <support/Mutex.h>

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
    void addOniceTimer(const boost::function<void ()> & handle,uint32_t interval);
    void addEveryTimer(const boost::function<void ()> & handle,uint32_t interval);
    void runOniceAfter(const boost::function<void ()> & handle,int interval);
    void runEveryInterval(const boost::function<void ()> & handle,int interval);

private:
    IOEventLoop* loop;
    int timerFd;
    boost::shared_ptr<IOEvent> event;
    Mutex mutex;
    std::multimap<uint64_t,boost::shared_ptr<Timer> > everyTimers;
    std::multimap<uint64_t,boost::shared_ptr<Timer> > oniceTimers;

    int createTimeFd();
    void timerHandle();
    bool needResetTimer(std::multimap<uint64_t,boost::shared_ptr<Timer> > & times,boost::shared_ptr<Timer> timer);
    void resetTimer(boost::shared_ptr<Timer> timer);
    void resetTimer();
    void readTimerfd();
};

}
}

#endif // AGILNET_NET_TIME_QUEUE
