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
    Timer(uint32_t interval,const boost::function<void ()> & funcHandle);
    struct timeval getTimeOut();
    uint64_t getTimeOutMSecond();
    struct timespec getTimeInterval();
    void update();
    void setHandle(const boost::function<void ()> &);

    static uint64_t getNowTimeMSecond();
    static std::string getNowTimeDate();
    
    void timerHandle();
private:
    uint32_t intervalMs;
    struct timeval now;
    boost::function<void ()> handle;
};

}
}
#endif // AGILNET_NET_TIME
