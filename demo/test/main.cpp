#include <boost/thread/thread.hpp> //包含boost头文件
#include <iostream>
#include <cstdlib>
#include <boost/asio.hpp>

#include "AtomicInt.h"

using namespace std;
using namespace agilNet;
int main()
{
    AtomicInt16 num;
    num.set(434);
    num.inc();
    num.add(4);
    cout<<num.get()<<endl;
    return 0;
}
