#include <IOEventLoop.h>


using namespace agilNet::net;

IOEventLoop::IOEventLoop()
    :eventCtrl(new IOEventCtrl(this))
{

}
void IOEventLoop::run()
{
    eventCtrl->waitAndRunHandle();
}
