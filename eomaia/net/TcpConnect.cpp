#include <net/TcpConnect.h>
#include <thread>
#include <base/LogInterface.h>
#include <iostream>
#include <cstring>
#include <functional>

using namespace eomaia::net;
using namespace std;

TcpConnect::TcpConnect(IOEventLoop* l,struct sockaddr_in addr,int fd)
    :loop(l),
    socketAddr(addr),
    name(socketAddr.toString()),
    socket(new Socket(fd)),
    event(new IOEvent(loop,fd)),
    state(Disconnecting)
{
    setNoDelay(true);
    loop->addEvent(event);
    event->setReadFunc(std::bind(&TcpConnect::readEvent,this));
    event->setCloseFunc(std::bind(&TcpConnect::closeEvent,this));
    event->setWriteFunc(std::bind(&TcpConnect::writeEvent,this));
    event->setErrorFunc(std::bind(&TcpConnect::errorEvent,this));

}

TcpConnect::~TcpConnect()
{
    event->disableAll();
    event->removeFromLoop();
}

void TcpConnect::setMessageCallback(const OnMessageCallback callback)
{
    messageCallback = callback;
}

void TcpConnect::setCloseCallback(const OnCloseCallback callback)
{
    closeCallback = callback;
}

void TcpConnect::setWriteCompletCallback(const OnWriteCompletCallback callback)
{
    writeCompleteCallback = callback;
}

void TcpConnect::readEvent()
{

    int error= 0;
    int n = readBuf.readFromIO(event->getFd(), error);
    if (n > 0)
    {
        if(messageCallback)
        {
            messageCallback(shared_from_this(),readBuf);
        }
    }
    else if (n == 0)
    {
        closeEvent();
    }
    else
    {
        base::Log::OUT(base::Log::Error) << "TcpConnection::handleRead error :"<<std::to_string(error);
        closeEvent();
    }
}

void TcpConnect::closeEvent()
{
    state = Disconnected;
    if(closeCallback)
    {
        closeCallback(shared_from_this());
    }
}

TcpConnect& TcpConnect::getRefer()
{
    return (*this);
}

const SocketAddr& TcpConnect::getAddr() const
{
    return socketAddr;
}

string TcpConnect::getName() const
{
    return name;
}


void TcpConnect::connectedHandle()
{
    state = Connected;
    event->enableReading(true);
    //epoll为电平触发
    //event->enableWriting(true);
    event->enableErrorEvent(true);
}

void TcpConnect::errorEvent()
{
    closeEvent();
}

void TcpConnect::writeEvent()
{
  //loop_->assertInLoopThread();
    if (event->isWriting())
    {
        int n = SocketOperation::write(event->getFd(),  writeBuf.readIndexPtr(),writeBuf.readableBytes());
        if (n > 0)
        {
            writeBuf.clearReadIndex(n);
            if (writeBuf.isEmpty())
            {
                event->enableWriting(false);
                if (writeCompleteCallback)
                {
                    std::shared_ptr<TcpConnect> tmp(this);
                    writeCompleteCallback(tmp);
                    if(writeCompleteCallback)
                        writeCompleteCallback( shared_from_this());
                }
            }
            /*
            if (state_ == kDisconnecting)
            {
              shutdownInLoop();
            }
            */
        }
        else
        {
            base::Log::OUT(base::Log::Error)<<"write data error";
        }
    }
    else
    {
        base::Log::OUT(base::Log::Warn) << "Connection fd = " << std::to_string(event->getFd()) << " is down, no more writing";
    }
}

void TcpConnect::write(const char* data)
{
    int len = ::strlen(data);
    write((void*)data,len);
}

void TcpConnect::write(const string& data)
{
    write(&(*data.begin()),data.length());
}

void TcpConnect::write(const void* data,uint32_t length)
{
    int n = 0;
    size_t remaining = length;
    bool faultError = false;
    if (state == Disconnected)
    {
        base::Log::OUT(base::Log::Warn) << "disconnected, give up writing";
        return;
    }

    //如该写数据缓冲区内有数据，直接写入socket缓冲区会导致数据交叠
    if (!event->isWriting() && writeBuf.isEmpty())
    {
        n = SocketOperation::write(event->getFd(), data, length);
        if (n >= 0)
        {
            remaining = length - n;
            if (remaining == 0 && writeCompleteCallback)
            {
                writeCompleteCallback(shared_from_this());
            }
        }
        else
        {
            n = 0;
            if (errno != EWOULDBLOCK)
            {
                base::Log::OUT(base::Log::Error)<<"write data error";
                if (errno == EPIPE || errno == ECONNRESET) // FIXME: any others?
                {
                    faultError = true;
                }
            }
        }
    }

    if (!faultError && remaining > 0)
    {
    #if 0
        size_t oldLen = outputBuffer_.readableBytes();
        if (oldLen + remaining >= highWaterMark_
            && oldLen < highWaterMark_
            && highWaterMarkCallback_)
        {
        loop_->queueInLoop(std::bind(highWaterMarkCallback_, shared_from_this(), oldLen + remaining));
        }
        #endif // 0
        writeBuf.append(static_cast<const char*>(data)+n, remaining);
        if (!event->isWriting())
        {
            event->enableWriting(true);
        }

    }

}

void TcpConnect::writeInLoop(const void* data, uint32_t len)
{
    loop->runInLoop([this,data,len]{
        write(data,len);
    });
}


void TcpConnect::setNoDelay(bool enable)
{
    socket->setTcpNoDelay(enable);
}

void TcpConnect::shutdownWrite()
{
    if (state == Connected)
    {
        state = Disconnecting;
        socket->shutdownWrite();
    }
}
