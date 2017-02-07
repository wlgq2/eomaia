#ifndef AGILNET_NET_IOEVENT
#define AGILNET_NET_IOEVENT

#include <boost/function.hpp>



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

    IOEvent(IOEventLoop* loop,int fd);
    ~IOEvent();
    int getFd();
    uint32_t getEvents();

    void enableReading(bool isEnable);
    void enableWriting(bool isEnable) ;
    void disableAll();
    bool isWriting();
    bool isReading();
    void removeFromLoop();

    void handle(uint32_t revents);

    void setReadFunc(boost::function<void()> func);
    void setWriteFunc(boost::function<void()> func);
    void setErrorFunc(boost::function<void()> func);
    void setCloseFunc(boost::function<void()> func);
private:
    IOEventLoop* eventLoop;
    void update();
    int eventFd;
    uint32_t events;
    boost::function<void()> readHandle;
    boost::function<void()> writeHandle;
    boost::function<void()> errorHandle;
    boost::function<void()> closeHandle;
};

}
}

#endif // AGILNET_NET_IOEVENT
