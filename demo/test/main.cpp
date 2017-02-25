#include <boost/thread/thread.hpp> //包含boost头文件
#include <iostream>
#include <cstdlib>
#include <boost/asio.hpp>

#include <AtomicInt.h>
#include <Condition.h>

#include <Socket.h>
#include <IOEventLoop.h>

using namespace std;
using namespace agilNet;
using namespace agilNet::net;

void accetp()
{
    cout<<"accetp"<<endl;
}
int main()
{

    boost::function<void( )> fun;
    fun = boost::bind(accetp);
    if(fun)
        fun();
    SocketAddr addr(true,10002);
    Socket socket(SocketOperation::createNonblockingSocket());
    socket.bind(addr);
    socket.listen();
    shared_ptr<IOEvent> e1(new IOEvent(socket.getFd()));
   // e1->setB
    e1->enableReading();
    e1->setReadFunc(boost::bind(accetp));
    IOEventLoop el;
    IOEventCtrl ec(&el);
    ec.addEvent(e1);
    el.run();
    return 0;

}
