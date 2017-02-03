#include <Buffer.h>
#include <errno.h>
#include <sys/uio.h>
#include <SocketOperation.h>


using namespace agilNet::net;

const uint32_t Buffer::InitSize = 1024;

Buffer::Buffer(uint32_t size)
    :readIndex(0),
    writeIndex(0),
    buffer(size)
{

}
Buffer::~Buffer()
{

}

void Buffer::append(const char* data, size_t len)
{
    ensureWritableBytes(len);
    std::copy(data, data+len,buffer.begin()+writeIndex);
    writeIndex+= len;
}



void Buffer::ensureWritableBytes(size_t len)
{
    if (writableBytes() < len)
    {
         buffer.resize(writeIndex+len);
    }
}

uint8_t Buffer::writableBytes()
{
    return buffer.size() - writeIndex;
}
int Buffer::readFromIO(int fd,int& errorNo)
{
    char extrabuf[65536];
    struct iovec vec[2];
    uint32_t writable = writableBytes();
    vec[0].iov_base = &(*buffer.begin())+writeIndex;
    vec[0].iov_len = writable;
    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof extrabuf;

    uint32_t iovcnt = (writable < sizeof extrabuf) ? 2 : 1;
    uint32_t n = SocketOperation::readv(fd, vec, iovcnt);
    if (n < 0)
    {
        errorNo = errno;
    }
    else if (n<= writable)
    {
        writeIndex += n;
    }
    else
    {
        writeIndex = buffer.size();
        append(extrabuf, n - writable);
    }
    return n;
}
