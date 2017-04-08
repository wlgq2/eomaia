#include <net/TcpConnect.h>
#include <boost/thread/thread.hpp>
#include <support/Log.h>
#include <iostream>


using namespace agilNet::log;
using namespace agilNet::net;
using namespace std;
using namespace boost;

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
    event->setReadFunc(boost::bind(&TcpConnect::readEvent,this));
    event->setCloseFunc(boost::bind(&TcpConnect::closeEvent,this));
    event->setWriteFunc(boost::bind(&TcpConnect::writeEvent,this));
    event->setErrorFunc(boost::bind(&TcpConnect::errorEvent,this));

}

TcpConnect::~TcpConnect()
{
    event->disableAll();
    event->removeFromLoop();
}


void TcpConnect::setMessageCallback(const boost::function<void ( boost::shared_ptr<TcpConnect>, Buffer&)> & callback)
{
    messageCallback = callback;
}

void TcpConnect::setCloseCallback(const boost::function<void (boost::shared_ptr<TcpConnect>)> & callback)
{
    closeCallback = callback;
}

void TcpConnect::setWriteCompletCallback(const boost::function<void (boost::shared_ptr<TcpConnect>)> & callback)
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
        LogOutput(error) << "TcpConnection::handleRead error :"<<error;
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
                    shared_ptr<TcpConnect> tmp(this);
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
            LogOutput(error)<<"write data error";
        }
    }
    else
    {
        LogOutput(warning) << "Connection fd = " << event->getFd() << " is down, no more writing";
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
        LogOutput(warning) << "disconnected, give up writing";
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
                LogOutput(error)<<"write data error";
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
        loop_->queueInLoop(boost::bind(highWaterMarkCallback_, shared_from_this(), oldLen + remaining));
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
    loop->runInLoop(boost::bind(&TcpConnect::write,this,data,len));
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
