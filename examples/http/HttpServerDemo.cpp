#include "HttpServerDemo.h"
#include <iostream>

#include <base/LogInterface.h>

using namespace eomaia::net;
using namespace std;

HttpServerDemo::HttpServerDemo(IOEventLoop* loop,SocketAddr& addr)
    :HttpServer(loop,addr)
{

}

//这里实际需要根据HttpRequest的内容来解析，发送HttpResponse。
void HttpServerDemo::httpCallback(const HttpRequest&, HttpResponse* resp)
{
    resp->setStatusCode(HttpResponse::k200Ok);
    resp->setStatusMessage("OK");
    resp->setBody("a test program base on eomaia lib. \nauthor:  object_he@yeah.net");
    resp->setCloseConnection(true);
}
