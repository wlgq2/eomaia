#ifndef AGILNET_NET_IOEVENT
#define AGILNET_NET_IOEVENT

namespace agilNet
{
namespace net
{
class IOEvent
{
public:
    static const int noneEventFlag;
    static const int readEventFlag;
    static const int writeEventFlag;

    IOEvent(int fd);
    ~IOEvent();
    int getFd();
    int getEvents();

    void enableReading();
    void disableReading() ;
    void enableWriting() ;
    void disableWriting() ;
    void disableAll();
    bool isWriting();
    bool isReading();

    void handle();
private:
    void update();
    int eventFd;
    int events;
};

}
}

#endif // AGILNET_NET_IOEVENT
