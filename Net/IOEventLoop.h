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
    void run();
private:
    IOEventCtrl* eventCtrl;
};
}
}
#endif // AGILNET_NET_IOEVENTLOOP
