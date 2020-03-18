#ifndef EOMAIA_NET_IOEVENTLOOP
#define EOMAIA_NET_IOEVENTLOOP


#include <thread>
#include <mutex>
#include <net/TimerQueue.h>
#include <net/IOEventCtrl.h>

namespace eomaia
{
namespace net
{
class IOEventLoop
{
public :
    IOEventLoop();
    ~IOEventLoop();

    void addEvent( std::shared_ptr<IOEvent> event);
    void removeEvent( std::shared_ptr<IOEvent> event);
    void modifyEvent( std::shared_ptr<IOEvent>  event);
    void modifyEvent(int fd);
    void removeEvent(int fd);
    void run();
    void runInLoop(const DefaultFunction func);
    void runOniceAfter(const DefaultFunction callback,uint32_t interval);
    void runEveryInterval(const DefaultFunction callback,uint32_t interval);

private:
    static const int PollTimeMs;
    std::mutex mutex;
    IOEventCtrl* eventCtrl;
    std::thread::id thisTheadId;
    std::shared_ptr<TimerQueue> timerQueue;

    std::vector<DefaultFunction> functions;

    void addFunInLoop(DefaultFunction func);

    bool inThisThread();
    void runAllFunctionInLoop();

};
}
}
#endif // EOMAIA_NET_IOEVENTLOOP
