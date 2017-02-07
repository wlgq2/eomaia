#include <Log.h>
#include <cstddef>
#include <Mutex.h>


using namespace std;
using namespace agilNet::support;

bool Log::isInit = false;
Log* Log::single;

Log::Log()
{
    boost::log::add_file_log("log/test.log", boost::log::keywords::auto_flush = true);
}
Log* Log::getSingle()
{
    //由于C++的内存模型，会导致双重检查锁失效。
    if((NULL == single)&&(!isInit))
    {
        Mutex mutex;
        MutexGuard mutexGuard(mutex);
        if(NULL == single)
        {
            single = new Log();
            isInit = true;
        }
    }
    return single;
}

void Log:: write(Level level,string& content )
{
    switch(level)
    {
        case trace:
            BOOST_LOG_TRIVIAL(trace) << content<<endl;
            break;
        case debug:
            BOOST_LOG_TRIVIAL(debug) << content<<endl;
            break;
        case info:
            BOOST_LOG_TRIVIAL(info) << content<<endl;
            break;
        case warning:
            BOOST_LOG_TRIVIAL(warning) << content<<endl;
            break;
        case error:
            BOOST_LOG_TRIVIAL(error) << content<<endl;
            break;
        case fatal:
            BOOST_LOG_TRIVIAL(fatal) << content<<endl;
            break;
    }
}


void Log:: write(Level level,char* content)
{
    string str(content);
    write(level,str);
}
