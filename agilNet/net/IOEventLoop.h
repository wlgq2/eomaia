#ifndef AGILNET_NET_IOEVENTLOOP
#define AGILNET_NET_IOEVENTLOOP


#include <boost/thread.hpp>
#include <support/Mutex.h>
#include <net/TimerQueue.h>
#include <net/IOEventCtrl.h>

namespace agilNet
{
namespace net
{
class IOEventLoop
{
public :
    IOEventLoop();
    ~IOEventLoop();

    void addEvent( boost::shared_ptr<IOEvent> event);
    void removeEvent( boost::shared_ptr<IOEvent> event);
    void modifyEvent( boost::shared_ptr<IOEvent>  event);
    void modifyEvent(int fd);
    void removeEvent(int fd);
    void run();
    void runInLoop(const boost::function<void ()> & func);
    void runOniceAfter(const boost::function<void ()> & callback,uint32_t interval);
    void runEveryInterval(const boost::function<void ()> & callback,uint32_t interval);

private:
    static const int PollTimeMs;
    Mutex mutex;
    IOEventCtrl* eventCtrl;
    boost::thread::id thisTheadId;
    boost::shared_ptr<TimerQueue> timerQueue;

    std::vector<boost::function<void ()> > functions;

    void addFunInLoop(boost::function<void ()> func);

    bool inThisThread();
    void runAllFunctionInLoop();

};
}
}
#endif // AGILNET_NET_IOEVENTLOOP
