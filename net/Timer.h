#ifndef AGILNET_NET_TIMER
#define AGILNET_NET_TIMER

#include <stdint.h>
#include <sys/time.h>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>


namespace agilNet
{
namespace net
{


class Timer
{
public:
    Timer(uint32_t interval,boost::function<void ()>* funcHandle);
    struct timeval getTimeOut();
    uint64_t getTimeOutMSencond();
    struct timespec getTimeInterval();
    void update();
    void setHandle(boost::shared_ptr<boost::function<void ()> >);

private:
    uint32_t intervalMs;
    struct timeval now;
    boost::shared_ptr<boost::function<void ()> >handle;
};

}
}
#endif // AGILNET_NET_TIME
