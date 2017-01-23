#include <boost/thread/thread.hpp> //包含boost头文件
#include <iostream>
#include <cstdlib>
#include <boost/asio.hpp>

#include "AtomicInt.h"
#include "Condition.h"

using namespace std;
using namespace agilNet;


Mutex mutex;
Condition condtion(mutex);
void func1()
{
    while(1)
    {
        condtion.notify();
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
}

void func2()
{
    while(1)
    {
        condtion.wait();
        cout << "func2:"<<endl;

    }
}

int main()
{

    AtomicInt16 num;
    num.set(434);
    num.inc();
    num.add(4);

    cout<<num.get()<<endl;

    boost::thread thread1(&func1);
    boost::thread thread2(&func2);

    thread2.join();
    thread1.join();
   while(1)
   {
        boost::this_thread::sleep(boost::posix_time::seconds(100));

   }
 //assert(false);
    return 0;
}
