#include <net/Buffer.h>
#include <net/http/HttpContext.h>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace agilNet::net;
using namespace agilNet;

bool HttpContext::processRequestLine(const char* begin, const char* end)
{
    bool succeed = false;
    const char* start = begin;
    const char* space = std::find(start, end, ' ');
    if (space != end && request.setMethod(start, space))
    {
        start = space+1;
        space = std::find(start, end, ' ');
        if (space != end)
        {
            const char* question = std::find(start, space, '?');
            if (question != space)
            {
                request.setPath(start, question);
                request.setQuery(question, space);
            }
            else
            {
                request.setPath(start, space);
            }
            start = space+1;
            succeed = end-start == 8 && std::equal(start, end-1, "HTTP/1.");
            if (succeed)
            {
                if (*(end-1) == '1')
                {
                    request.setVersion(HttpRequest::Http11);
                }
                else if (*(end-1) == '0')
                {
                    request.setVersion(HttpRequest::Http10);
                }
                else
                {
                    succeed = false;
                }
            }
        }
    }
    return succeed;
}


bool HttpContext::parseRequest(Buffer* buf, string receiveTime)
{
    bool ok = true;
    bool hasMore = true;
    while (hasMore)
    {
        if (state == ExpectRequestLine)
        {
            const char* crlf = buf->findCRLF();
            if (crlf)
            {
                ok = processRequestLine((const char*)(buf->readIndexPtr()), crlf);
                if (ok)
                {
                    request.setReceiveTime(receiveTime);
                    buf->retrieveUntil(crlf + 2);
                    state = ExpectHeaders;
                }
                else
                {
                    hasMore = false;
                }
            }
            else
            {
                hasMore = false;
            }
        }
        else if (state == ExpectHeaders)
        {
            const char* crlf = buf->findCRLF();
            if (crlf)
            {
                const char* colon = std::find((const char*)buf->readIndexPtr(), crlf, ':');
                if (colon != crlf)
                {
                    request.addHeader((const char*)buf->readIndexPtr(), colon, crlf);
                }
                else
                {
                    state = GotAll;
                    hasMore = false;
                }
                buf->retrieveUntil(crlf + 2);
            }
            else
            {
                hasMore = false;
            }
        }
        else if (state == ExpectBody)
        {

        }
    }
    return ok;
}
