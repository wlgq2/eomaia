#ifndef AGILNET_NET_IOEVENTCTRL
#define AGILNET_NET_IOEVENTCTRL

#include <map>
#include <vector>

#include <boost/weak_ptr.hpp>
#include <net/Epoll.h>
#include <net/IOEvent.h>



namespace agilNet
{

namespace net
{

class IOEventLoop;

class IOEventCtrl
{
public:
    IOEventCtrl(IOEventLoop* l);
    ~IOEventCtrl();
    void addEvent(boost::shared_ptr<IOEvent> event);
    void deleteEvent(boost::shared_ptr<IOEvent> event);
    void modifyEvent(boost::shared_ptr<IOEvent> event);
    void modifyEvent(int fd);
    void deleteEvent(int fd);
    void waitAndRunHandle(int timeMs);
private:
    static const int activeEventLength;
    std::map<int,boost::weak_ptr<IOEvent> > eventPool;

    Epoll epoll;
    IOEventLoop* loop;
    std::vector<struct epoll_event> activeEvents;
};

}
}
#endif // AGILNET_NET_IOEVENTCTRL
