#ifndef AGILNET_SUPPORT_ATOMIC_H
#define AGILNET_SUPPORT_ATOMIC_H

#include <boost/noncopyable.hpp>
#include <stdint.h>

namespace agilNet
{

namespace detail
{
template<typename T>
class AtomicInt  : boost::noncopyable
{
public:
    AtomicInt(T x =0)
      //: value(x)
    {
        set(x);
    }

    T get()
    {
        return __sync_val_compare_and_swap(&value, 0, 0);
    }
    void set(T newValue)
    {
        getAndSet(newValue);
    }

    T getAndSet(T newValue)
    {
        return __sync_lock_test_and_set(&value, newValue);
    }

    T getAndAdd(T x)
    {
        return __sync_fetch_and_add(&value, x);
    }

    T addAndGet(T x)
    {
        return __sync_add_and_fetch(&value,x);
    }

    T incAndGet()
    {
        return addAndGet(1);
    }

    T decAndGet()
    {
        return addAndGet(-1);
    }

    T getAndDec()
    {
        return getAndAdd(-1);
    }

    T getAndInc()
    {
        return addAndGet(1);
    }


    void add(T x)
    {
        getAndAdd(x);
    }

    void inc()
    {
        getAndInc();
    }

    void dec()
    {
        getAndDec();
    }



private:
    volatile T value;
};
}

typedef detail::AtomicInt<int8_t>  AtomicInt8;
typedef detail::AtomicInt<int16_t> AtomicInt16;
typedef detail::AtomicInt<int32_t> AtomicInt32;
typedef detail::AtomicInt<int64_t> AtomicInt64;
}

#endif  // MUDUO_BASE_ATOMIC_H
