#include <IOEventLoop.h>


using namespace agilNet::net;

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
    eventCtrl->waitAndRunHandle();
}
