#ifndef AGILNET_DOME_HTTPSERVERDOME
#define AGILNET_DOME_HTTPSERVERDOME

#include <net/http/HttpServer.h>



class HttpServerDemo : public agilNet::net::HttpServer
{
public:
    HttpServerDemo(agilNet::net::IOEventLoop* loop,agilNet::net::SocketAddr& addr);

    virtual void httpCallback(const agilNet::net::HttpRequest&, agilNet::net::HttpResponse*);

};

#endif
