#ifndef AGILNET_NET_IOEVENTCTRL
#define AGILNET_NET_IOEVENTCTRL

#include <map>
#include <vector>
#include <IOEvent.h>
#include <boost/weak_ptr.hpp>
#include <Epoll.h>


using namespace std;
using namespace boost;

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
    void addEvent(shared_ptr<IOEvent> event);
    void deleteEvent(shared_ptr<IOEvent> event);
    void modifyEvent(shared_ptr<IOEvent> event);
    void modifyEvent(int fd);
    void deleteEvent(int fd);
    void waitAndRunHandle(int timeMs);
private:
    static const int activeEventLength;
    map<int,weak_ptr<IOEvent> > eventPool;

    Epoll epoll;
    IOEventLoop* loop;
    vector<struct epoll_event> activeEvents;
};

}
}
#endif // AGILNET_NET_IOEVENTCTRL
