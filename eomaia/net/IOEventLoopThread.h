#ifndef EOMAIA_IOEVENTLOOPTHREAD
#define EOMAIA_IOEVENTLOOPTHREAD

#include <base/Thread.h>
#include <condition_variable>
#include <net/IOEventLoop.h>


namespace eomaia
{

namespace net
{
class IOEventLoopThread : public base::Thread
{
public :
    IOEventLoopThread();
    virtual void run();
    IOEventLoop* getLoopInThread();
private:
    IOEventLoop* loop;
    std::mutex mutex;
    std::condition_variable condtion;
};

}

}

#endif // EOMAIA_IOEVENTLOOPTHREAD
