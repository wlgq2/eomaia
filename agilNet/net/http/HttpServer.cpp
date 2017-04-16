#include <net/http/HttpServer.h>
#include <net/http/HttpContext.h>
#include <iostream>

#include <support/Log.h>

using namespace agilNet::log;
using namespace agilNet::net;
using namespace std;


HttpServer::HttpServer(IOEventLoop* loop,SocketAddr& addr)
    :TcpServer(loop,addr)
{

}

HttpServer::~HttpServer()
{

}

void HttpServer::connectCallback(boost::shared_ptr<TcpConnect> tcpConnect)
{

}

void HttpServer::messageCallback(boost::shared_ptr<TcpConnect> tcpConnect, Buffer& buffer)
{
    HttpContext  context;
    if (!context.parseRequest(&buffer, Timer::getNowTimeDate()))
    {
        tcpConnect->write("HTTP/1.1 400 Bad Request\r\n\r\n");
        tcpConnect->shutdownWrite();
    }

    if (context.gotAll())
    {
        onRequest(tcpConnect, context.getRequest());
        context.reset();
    }
}
void HttpServer::writeCompletCallback(boost::shared_ptr<TcpConnect> tcpConnect)
{

}

void HttpServer::connectCloseCallback(boost::shared_ptr<TcpConnect> connect)
{

}

void HttpServer::httpCallback(const HttpRequest&, HttpResponse* resp)
{
    resp->setStatusCode(HttpResponse::k404NotFound);
    resp->setStatusMessage("Not Found");
    resp->setCloseConnection(true);
}

void HttpServer::onRequest( boost::shared_ptr<TcpConnect> conn, const HttpRequest& req)
{
    const string& connection = req.getHeader("Connection");
    bool close = connection == "close" ||(req.getVersion() == HttpRequest::Http10 && connection != "Keep-Alive");
    HttpResponse response(close);

    httpCallback(req, &response);
    Buffer buf;
    response.appendToBuffer(&buf);
    string str;
    buf.readAllAsString(str);
    conn->write(str);
    if (response.getCloseConnection())
    {
        conn->shutdownWrite();
    }
}

