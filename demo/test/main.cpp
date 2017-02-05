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
    IOEventLoop loop;
    boost::function<void( )> fun;
    fun = boost::bind(accetp);
    if(fun)
        fun();
    SocketAddr addr(true,10002);
    Socket socket(SocketOperation::createNonblockingSocket());
    socket.bind(addr);
    socket.listen();
    shared_ptr<IOEvent> event(new IOEvent(&loop,socket.getFd()));
   // e1->setB
    event->enableReading(true);
    event->setReadFunc(boost::bind(accetp));

//    loop.addEvent(event);
    loop.run();
    return 0;

}
