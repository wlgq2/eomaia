#ifndef EOMAIA_NET_IOEVENT
#define EOMAIA_NET_IOEVENT

#include <functional>

using DefaultFunction = std::function<void()>;

namespace eomaia
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
    static const int errorEventFlag;

    IOEvent(IOEventLoop* loop,int fd);
    ~IOEvent();
    int getFd();
    uint32_t getEvents();

    void enableReading(bool isEnable);
    void enableWriting(bool isEnable) ;
    void enableErrorEvent(bool isEnable) ;
    void disableAll();
    bool isWriting();
    bool isReading();
    void removeFromLoop();

    void handle(uint32_t revents);

    void setReadFunc(const DefaultFunction & func);
    void setWriteFunc(const DefaultFunction & func);
    void setErrorFunc(const DefaultFunction & func);
    void setCloseFunc(const DefaultFunction & func);
private:
    IOEventLoop* eventLoop;
    void update();
    int eventFd;
    uint32_t events;
    DefaultFunction readHandle;
    DefaultFunction writeHandle;
    DefaultFunction errorHandle;
    DefaultFunction closeHandle;
};

}
}

#endif // EOMAIA_NET_IOEVENT
