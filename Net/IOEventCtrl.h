#ifndef AGILNET_NET_IOEVENTCTRL
#define AGILNET_NET_IOEVENTCTRL

#include <map>
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
    void addEvent(shared_ptr<IOEvent> event);
    void deleteEvent(shared_ptr<IOEvent> event);
    void modifyEvent(shared_ptr<IOEvent> event);
    void waitAndRunHandle();
private:
    map<int,weak_ptr<IOEvent> > eventPool;
    Epoll epoll;
    IOEventLoop* loop;
};

}
}
#endif // AGILNET_NET_IOEVENTCTRL
