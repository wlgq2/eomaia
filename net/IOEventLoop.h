#ifndef AGILNET_NET_IOEVENTLOOP
#define AGILNET_NET_IOEVENTLOOP

#include <IOEventCtrl.h>
#include <boost/thread.hpp>
#include <Mutex.h>

namespace agilNet
{
namespace net
{
class IOEventLoop
{
public :
    IOEventLoop();
    ~IOEventLoop();

    void addEvent(boost::shared_ptr<IOEvent> event);
    void removeEvent(boost::shared_ptr<IOEvent> event);
    void modifyEvent(boost::shared_ptr<IOEvent> event);
    void modifyEvent(int fd);
    void removeEvent(int fd);
    void run();
    void runInLoop(boost::function<void ()> func);

private:
    static const int PollTimeMs;
    Mutex mutex;
    IOEventCtrl* eventCtrl;
    boost::thread::id thisTheadId;
    std::vector<boost::function<void ()> > functions;
    void addFunInLoop(boost::function<void ()> func);

    bool inThisThread();
    void runAllFunctionInLoop();

};
}
}
#endif // AGILNET_NET_IOEVENTLOOP
