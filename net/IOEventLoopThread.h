#ifndef AGILNET_IOEVENTLOOPTHREAD
#define AGILNET_IOEVENTLOOPTHREAD

#include <Thread.h>

namespace agilNet
{

namespace net
{
class IOEventLoopThread : public agilNet::thread::Thread
{
public :
    virtual void run();

};

}

}

#endif // AGILNET_IOEVENTLOOPTHREAD
