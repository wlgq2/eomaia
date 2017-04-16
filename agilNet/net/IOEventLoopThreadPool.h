#ifndef AGILNET_NET_IOEVENTLOOPTHREADPOOL
#define AGILNET_NET_IOEVENTLOOPTHREADPOOL

#include <vector>
#include <boost/shared_ptr.hpp>

#include <net/IOEventLoopThread.h>
#include <net/IOEventLoop.h>

namespace agilNet
{
namespace net
{
class IOEventLoopThreadPool
{
public:
    IOEventLoopThreadPool(IOEventLoop* loop);
    void init();
    void init(int num );
    bool isStarted();
    void setThreadNum(uint16_t num);

    IOEventLoop* getOneLoopFromPool();
    IOEventLoop* getOneLoopFromPoolWithHash(int hashCode);

private:
    IOEventLoop* mainLoop;
    bool started;
    uint16_t threadNum;
    uint32_t threadIndex;
    std::vector<boost::shared_ptr<IOEventLoopThread> >threadPool;
    std::vector<IOEventLoop* > eventLoopPool;
};

}
}

#endif // AGILNET_NET_IOEVENTLOOPTHREADPOOL
