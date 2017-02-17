#include <iostream>
#include <support/Log.h>
#include <net/IOEventLoop.h>
#include <net/IOEventLoopThread.h>
#include <boost/function.hpp>

using namespace std;
using namespace agilNet::log;
using namespace agilNet::net;
using namespace boost;

class TimerCallback
{
public:
    static void callback1()
    {
        cout<<"callback 1 test"<<endl;
    }
    static void callback2()
    {
        cout<<"callback 2 test"<<endl;
    }
    static void callback3()
    {
        cout<<"callback 3 test"<<endl;
    }
    static void callback4()
    {
        cout<<"callback 4 test"<<endl;
    }
};

int main()
{
    //创建主循环事件分发器
    IOEventLoop loop;
    //增加定时运行一次事件
    loop.runOniceAfter(bind(&TimerCallback::callback1),2000);
    loop.runOniceAfter(bind(&TimerCallback::callback2),1500);
    //增加定时间隔时间运行
    loop.runEveryInterval(bind(&TimerCallback::callback3),2100);
    //事件循环机制运行
    loop.run();
}
