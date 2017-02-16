#ifndef AGILNET_THREAD
#define AGILNET_THREAD

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <support/Condition.h>


namespace agilNet
{
namespace thread
{

class Thread
{
public :
    Thread();
    //Thread 类总是被继承，虚析构会安全。
    virtual ~Thread();
    void start();

    //
    static boost::thread::id getNowThreadId();
    bool isStarted();
    //该函数为实际线程函数，子类需要实现。
    virtual void run()=0;
protected:
    //延迟函数只有在线程或者继承类中使用比较安全
    void sleepSeconds(int seconds);
private:
    //在该函数内阻塞，直到用start()函数。
    void beginRun();
    bool started;
    Mutex mutex;
    Condition condtion;
    boost::shared_ptr<boost::thread> thread;

};


}
}

#endif // THREAD_H_INCLUDED
