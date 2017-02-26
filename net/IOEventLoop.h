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

    void addEvent(shared_ptr<IOEvent> event);
    void removeEvent(shared_ptr<IOEvent> event);
    void modifyEvent(shared_ptr<IOEvent> event);
    void run();
private:
    static const int PollTimeMs;
    IOEventCtrl* eventCtrl;
};
}
}
#endif // AGILNET_NET_IOEVENTLOOP
