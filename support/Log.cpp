#include <Log.h>
#include <cstddef>
#include <Mutex.h>



using namespace std;
using namespace agilNet::support;

bool Log::isInit = false;
Log* Log::single = new Log;
const long long Log::FileSize = 10*1024*10247;

Log::Log()
{
    boost::log::add_file_log("log/agilNet-%Y-%m-%d_%H-%M-%S.%N.log",
        boost::log::keywords::rotation_size=FileSize,
        boost::log::keywords::auto_flush = true,
        boost::log::keywords::format= "[%TimeStamp%]: %Message%"
 );
  boost::log::add_common_attributes();
    using namespace boost::log::trivial;
   //  boost::log::trivial:: src::severity_logger< severity_level > lg;

}

Log* Log::getSingle()
{
    return single;
}

void Log:: write(Level level,const string& content )
{
	//这个丑陋的分支主要是因为BOOST_LOG_TRIVIAL是个宏
    switch(level)
    {
        case trace:
            BOOST_LOG_TRIVIAL(trace) << content;
            break;
        case debug:
            BOOST_LOG_TRIVIAL(debug) << content;
            break;
        case info:
            BOOST_LOG_TRIVIAL(info) << content;
            break;
        case warning:
            BOOST_LOG_TRIVIAL(warning) << content;
            break;
        case error:
            BOOST_LOG_TRIVIAL(error) << content;
            break;
        case fatal:
            BOOST_LOG_TRIVIAL(fatal) << content;
            break;
    }
}
