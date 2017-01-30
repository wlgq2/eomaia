#include <boost/thread/thread.hpp> //包含boost头文件
#include <iostream>
#include <cstdlib>
#include <boost/asio.hpp>

#include <AtomicInt.h>
#include <Condition.h>
#include <SocketAddr.h>

using namespace std;
using namespace agilNet;
using namespace agilNet::net;


int main()
{

    SocketAddr addr("15.63.57.47:4512");
    if(!addr.isValid())
    {
        cout<<"error"<<endl;
        return -1;
    }
    struct sockaddr_in haha = addr.getAddr();
    cout<<"addr"<<haha.sin_addr.s_addr<<endl;
    cout<<"port"<<htons(haha.sin_port)<<endl;
    return 0;

}
