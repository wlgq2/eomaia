#ifndef AGILNET_NET_HTTPCONTEXT
#define AGILNET_NET_HTTPCONTEXT



#include <net/http/HttpRequest.h>

namespace agilNet
{
namespace net
{

class Buffer;

class HttpContext
{
public:
    enum HttpRequestParseState
    {
        ExpectRequestLine,
        ExpectHeaders,
        ExpectBody,
        GotAll,
    };

    HttpContext()
        : state(ExpectRequestLine)
    {
    }

    bool parseRequest(Buffer* buf, string receiveTime);

    bool gotAll() const
    {
        return state == GotAll;
    }

    void reset()
    {
        state = ExpectRequestLine;
        HttpRequest dummy;
        request.swap(dummy);
    }

    const HttpRequest& getRequest() const
    {
        return request;
    }

private:
    bool processRequestLine(const char* begin, const char* end);

    HttpRequestParseState state;
    HttpRequest request;
};

}
}

#endif  // MUDUO_NET_HTTP_HTTPCONTEXT_H
