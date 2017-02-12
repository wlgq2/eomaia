#include <IOEventLoopThread.h>
#include <iostream>

using namespace agilNet::net;
using namespace std;

void IOEventLoopThread::run()
{
    while(true)
    {
        cout<<"thread id:"<<getThreadPtrId()<<endl;
        sleepSeconds(1);
    }
}
