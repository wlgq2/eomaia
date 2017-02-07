#ifndef AGILNET_NET_BUFFER
#define AGILNET_NET_BUFFER
#include <vector>
#include <stdint.h>


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

    uint8_t writableBytes() ;

    void append(const char*  data, std::size_t len);
    void ensureWritableBytes(std::size_t len);

private:
    uint32_t readIndex;
    uint32_t writeIndex;
    std::vector<uint8_t> buffer;
};
}
}
#endif // AGILNET_NET_BUFFER
