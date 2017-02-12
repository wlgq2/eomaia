#ifndef AGILNET_IOEVENTLOOPTHREAD
#define AGILNET_IOEVENTLOOPTHREAD

#include <Thread.h>
#include <IOEventLoop.h>
#include <Condition.h>

namespace agilNet
{

namespace net
{
class IOEventLoopThread : public agilNet::thread::Thread
{
public :
    IOEventLoopThread();
    virtual void run();
    IOEventLoop* getLoopInThread();
private:
    IOEventLoop* loop;
    Mutex mutex;
    Condition condtion;
};

}

}

#endif // AGILNET_IOEVENTLOOPTHREAD
