#ifndef EOMAIA_NET_IOEVENTCTRL
#define EOMAIA_NET_IOEVENTCTRL

#include <map>
#include <vector>

#include <memory>
#include <net/Epoll.h>
#include <net/IOEvent.h>



namespace eomaia
{

namespace net
{

class IOEventLoop;

class IOEventCtrl
{
public:
    IOEventCtrl(IOEventLoop* l);
    ~IOEventCtrl();
    void addEvent(std::shared_ptr<IOEvent> event);
    void deleteEvent(std::shared_ptr<IOEvent> event);
    void modifyEvent(std::shared_ptr<IOEvent> event);
    void modifyEvent(int fd);
    void deleteEvent(int fd);
    void waitAndRunHandle(int timeMs);
private:
    static const int activeEventLength;
    std::map<int,std::weak_ptr<IOEvent> > eventPool;

    Epoll epoll;
    IOEventLoop* loop;
    std::vector<struct epoll_event> activeEvents;
};

}
}
#endif // EOMAIA_NET_IOEVENTCTRL
