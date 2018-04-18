#ifndef AGILNET_NET_BUFFER
#define AGILNET_NET_BUFFER


#include <vector>
#include <stdint.h>
#include <iostream>
#include <algorithm>

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
    void append(const std::string& str);

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

    int readAllAsString(std::string & readBuf)
    {
        return readAsString(readableBytes(),readBuf);
    }

    int readAsString(uint32_t len,std::string & readBuf)
    {
        if(len > readableBytes())
            len = readableBytes();
        readBuf.assign((const char *)readIndexPtr(), len);
        clearReadIndex(len);
        return len;
    }

    int readAllAsByte(std::vector<uint8_t>& data)
    {
        return readBytes(data,readableBytes());
    }

    int readBytes(std::vector<uint8_t>& data,uint32_t len)
    {
        if(len > readableBytes())
            len = readableBytes();
        data.assign(readIndexPtr(), readIndexPtr()+len);
        clearReadIndex(len);
        return len;
    }

    void swap(Buffer& rhs);


    const char* findCRLF() const
    {
        char kCRLF[] = "\r\n";
       // const char* writePtr = bufferPtr()+writeIndex;
        const char* crlf = std::search((char*)readIndexPtr(),(char *)bufferPtr()+writeIndex, kCRLF, kCRLF+2);
        return crlf == ((char*)bufferPtr()+writeIndex) ? NULL : crlf;
    }
    void retrieveUntil(const char* end)
    {
        if(!(readIndexPtr() <= (uint8_t*)end))
        {
            std::cout<<"error retrieveUntil"<<std::endl;
            return ;
        }
        if(!(end <=  ((char*)bufferPtr()+writeIndex) ))
        {
            std::cout<<"error retrieveUntil"<<std::endl;
            return ;
        }
        clearReadIndex((uint8_t*)end - readIndexPtr());
    }
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
