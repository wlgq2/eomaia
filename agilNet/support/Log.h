#ifndef AGILNET_SUPPORT_LOG
#define AGILNET_SUPPORT_LOG

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <iostream>
#include <map>


#define         LogEable          1

#if   LogEable
#define         LogOutput(a)      BOOST_LOG_TRIVIAL(a)
#else
#define         LogOutput(a)      agilNet::log::Log::idleOutput()
#endif // LogEable

namespace agilNet
{
namespace log
{

class Log
{
public :
    enum Level
    {
        trace,
        debug,
        info,
        warning,
        error,
        fatal
    };

    void write(Level level,const std::string& content);
    void write(Level level,const char* content)
    {
        std::string str(content);
        write(level,str);
    }

    Log& operator<<( std::ostream& (*op) (std::ostream&))
    {
        return getSingleRefer();
    }

    Log& operator<<(const char* charPtr)
    {
        std::string str(charPtr);
        write(fatal,str);
        return getSingleRefer();
    }
    Log& operator<<(const int num)
    {
        std::stringstream stream;
        stream<<num;
        write(fatal,stream.str());
        return getSingleRefer();
    }

    Log& operator<<(const double num)
    {
        std::stringstream stream;
        stream<<num;
        write(fatal,stream.str());
        return getSingleRefer();
    }

    Log& operator<<(const float num)
    {
        std::stringstream stream;
        stream<<num;
        write(fatal,stream.str());
        return getSingleRefer();
    }

    Log& operator<<(const std::string& str)
    {
        write(fatal,str);
        return getSingleRefer();
    }

    static Log* getSingle();
    static Log& getSingleRefer()
    {
        return *getSingle();
    }

    static Log& idleOutput();
private :
    Log();
    static const long long FileSize;
    static Log* single;
    static bool isInit;
    std::map<Level,std::string> severityMap;
};




}
}
#endif // AGILNET_SUPPORT_LOG
