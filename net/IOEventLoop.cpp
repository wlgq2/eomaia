#include <IOEventLoop.h>


using namespace agilNet::net;

const int IOEventLoop::PollTimeMs = 3000;
IOEventLoop::IOEventLoop()
    :eventCtrl(new IOEventCtrl(this))
{

}

IOEventLoop::~IOEventLoop()
{
    delete eventCtrl;
}
void IOEventLoop::run()
{
    while(true)
    {
        eventCtrl->waitAndRunHandle(PollTimeMs);
    }
}
