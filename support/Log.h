#ifndef AGILNET_SUPPORT_LOG
#define AGILNET_SUPPORT_LOG

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <iostream>

namespace agilNet
{
namespace support
{
class Log
{
private :
    Log();

    static Log* single;
    static bool isInit;
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

    void write(Level level,std::string& content);
    void write(Level level,char* content);
    static Log* getSingle();
};
}
}
#endif // AGILNET_SUPPORT_LOG
