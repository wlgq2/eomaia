#include <cstddef>
#include <support/Mutex.h>
#include <support/Log.h>


using namespace std;
using namespace agilNet::log;

bool Log::isInit = false;
Log* Log::single = new Log;
const long long Log::FileSize = 10*1024*1024;

Log::Log()
{
    boost::log::add_file_log("log/agilNet-%Y-%m-%d_%H-%M-%S.%N.log",
        boost::log::keywords::rotation_size=FileSize,
        boost::log::keywords::auto_flush = true,
        boost::log::keywords::format=  "[%TimeStamp%] %Message%"
 );
    boost::log::add_common_attributes();

    severityMap.insert(pair<Level,string >(trace,"trace"));
    severityMap.insert(pair<Level,string >(debug,"debug"));
    severityMap.insert(pair<Level,string >(info,"info"));
    severityMap.insert(pair<Level,string >(warning,"warning"));
    severityMap.insert(pair<Level,string >(error,"error"));
    severityMap.insert(pair<Level,string >(fatal,"fatal"));
}

Log* Log::getSingle()
{
    return single;
}

void Log:: write(Level level,const string& content )
{
#if   LogEable
    LogOutput(fatal)<<severityMap[level]<<": "<<content;
#endif
}

Log& Log::idleOutput()
{
    return getSingleRefer();
}
