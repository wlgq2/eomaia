#ifndef AGILNET_NET_IOEVENTLOOP
#define AGILNET_NET_IOEVENTLOOP

#include <IOEventCtrl.h>

namespace agilNet
{
namespace net
{
class IOEventLoop
{
public :
    IOEventLoop();
    ~IOEventLoop();

    void addEvent(boost::shared_ptr<IOEvent> event);
    void removeEvent(boost::shared_ptr<IOEvent> event);
    void modifyEvent(boost::shared_ptr<IOEvent> event);
    void modifyEvent(int fd);
    void removeEvent(int fd);
    void run();
private:
    static const int PollTimeMs;
    IOEventCtrl* eventCtrl;
};
}
}
#endif // AGILNET_NET_IOEVENTLOOP
