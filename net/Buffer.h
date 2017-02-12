#ifndef AGILNET_NET_BUFFER
#define AGILNET_NET_BUFFER
#include <vector>
#include <stdint.h>
#include <iostream>

//这个类不是线程安全的。
namespace agilNet
{

namespace net
{

class Buffer
{
public:
    static const uint32_t InitSize;
    Buffer(uint32_t size=InitSize);
    ~Buffer();
    int readFromIO(int fd,int& errorNo);

    uint32_t writableBytes() ;
    uint32_t readableBytes() const;
    bool isReadble()
    {
        return  readableBytes()>0?true:false;
    }

    bool isEmpty()
    {
        return !isReadble();
    }

    void append(const char*  data, std::size_t len);
    void ensureWritableBytes(std::size_t len);

    const uint8_t* readIndexPtr() const
    {
        return bufferPtr() + readIndex;
    }

    void resetIndex()
    {
        readIndex = 0;
        writeIndex = 0;
    }

    void clearReadIndex(uint32_t len)
    {
        if (len < readableBytes())
        {
            readIndex += len;
        }
        else
        {
            resetIndex();
        }
    }

    std::string readAllAsString()
    {
        return readAsString(readableBytes());
    }

    std::string readAsString(uint32_t len)
    {
        if(len > readableBytes())
            len = readableBytes();
        std::string rst((const char *)readIndexPtr(), len);
        clearReadIndex(len);
        return rst;
    }

    std::vector<uint8_t> readAllAsByte()
    {
        return readBytes(readableBytes());
    }

    std::vector<uint8_t> readBytes(uint32_t len)
    {
        if(len > readableBytes())
            len = readableBytes();
        std::vector<uint8_t> rst(readIndexPtr(), readIndexPtr()+len);
        clearReadIndex(len);
        return rst;
    }
    void swap(Buffer& rhs);
private:
    uint32_t readIndex;
    uint32_t writeIndex;

    std::vector<uint8_t> buffer;

    const uint8_t* bufferPtr() const
    {
        return &(*buffer.begin());
    }

};
}
}
#endif // AGILNET_NET_BUFFER
