#ifndef AGILNET_NET_IOEVENT
#define AGILNET_NET_IOEVENT

#include <boost/function.hpp>



using namespace boost;
namespace agilNet
{
namespace net
{
class IOEventLoop;

class IOEvent
{
public:
    static const int noneEventFlag;
    static const int readEventFlag;
    static const int writeEventFlag;

    IOEvent(int fd);
    ~IOEvent();
    int getFd();
    uint32_t getEvents();

    void enableReading();
    void disableReading() ;
    void enableWriting() ;
    void disableWriting() ;
    void disableAll();
    bool isWriting();
    bool isReading();

    void handle(uint32_t revents);

    void setReadFunc(function<void()> func);
    void setWriteFunc(function<void()> func);
    void setErrorFunc(function<void()> func);
    void setCloseFunc(function<void()> func);
private:
    void update();
    int eventFd;
    uint32_t events;
    function<void()> readHandle;
    function<void()> writeHandle;
    function<void()> errorHandle;
    function<void()> closeHandle;
};

}
}

#endif // AGILNET_NET_IOEVENT
