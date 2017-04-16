#ifndef AGILNET_NET_HTTPREQUEST
#define AGILNET_NET_HTTPREQUEST


#include <map>
#include <assert.h>
#include <stdio.h>
#include <iostream>

namespace agilNet
{
namespace net
{
using namespace std;

class HttpRequest
{
public:
    enum Method
    {
        Invalid, Get, Post, Head, Put, Delete
    };
    enum Version
    {
        Unknown, Http10, Http11
    };

    HttpRequest()
      : method(Invalid),
        version(Unknown)
    {
    }

    void setVersion(Version v)
    {
        version = v;
    }

    Version getVersion() const
    {
        return version;
    }

    bool setMethod(const char* start, const char* end)
    {
        assert(method == Invalid);
        string m(start, end);
        if (m == "GET")
        {
            method = Get;
        }
        else if (m == "POST")
        {
            method = Post;
        }
        else if (m == "HEAD")
        {
            method = Head;
        }
        else if (m == "PUT")
        {
            method = Put;
        }
        else if (m == "DELETE")
        {
            method = Delete;
        }
        else
        {
            method = Invalid;
        }
        return method != Invalid;
    }

    Method getMethod() const
    {
        return method;
    }

    const char* methodString() const
    {
        const char* result = "UNKNOWN";
        switch(method)
        {
            case Get:
                result = "GET";
                break;
            case Post:
                result = "POST";
                break;
            case Head:
                result = "HEAD";
                break;
            case Put:
                result = "PUT";
                break;
            case Delete:
                result = "DELETE";
                break;
            default:
                break;
        }
        return result;
    }

    void setPath(const char* start, const char* end)
    {
        path.assign(start, end);
    }

    const string& getPath() const
    {
        return path;
    }

    void setQuery(const char* start, const char* end)
    {
        query.assign(start, end);
    }

    const string& getQuery() const
    {
        return query;
    }

    void setReceiveTime(string& t)
    {
        receiveTime = t;
    }

    string getReceiveTime() const
    {
        return receiveTime;
    }

    void addHeader(const char* start, const char* colon, const char* end)
    {
        string field(start, colon);
        ++colon;
        while (colon < end && isspace(*colon))
        {
            ++colon;
        }
        string value(colon, end);
        while (!value.empty() && isspace(value[value.size()-1]))
        {
            value.resize(value.size()-1);
        }
        headers[field] = value;
    }

    string getHeader(const string& field) const
    {
        string result;
        std::map<string, string>::const_iterator it = headers.find(field);
        if (it != headers.end())
        {
            result = it->second;
        }
        return result;
    }

    const std::map<string, string>& getHeaders() const
    {
        return headers;
    }

    void swap(HttpRequest& that)
    {
        std::swap(method, that.method);
        std::swap(version, that.version);
        path.swap(that.path);
        query.swap(that.query);
        receiveTime.swap(that.receiveTime);
        headers.swap(that.headers);
    }

private:
    Method method;
    Version version;
    string path;
    string query;
    string receiveTime;
    std::map<string, string> headers;
};

}
}

#endif  // MUDUO_NET_HTTP_HTTPREQUEST_H
