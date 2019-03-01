#ifndef EOMAIA_DOME_HTTPSERVERDOME
#define EOMAIA_DOME_HTTPSERVERDOME

#include <net/http/HttpServer.h>



class HttpServerDemo : public eomaia::net::HttpServer
{
public:
    HttpServerDemo(eomaia::net::IOEventLoop* loop,eomaia::net::SocketAddr& addr);

    virtual void httpCallback(const eomaia::net::HttpRequest&, eomaia::net::HttpResponse*);

};

#endif
