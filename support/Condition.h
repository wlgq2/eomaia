#ifndef AGILNET_SUPPORT_CONDITION_H
#define AGILNET_SUPPORT_CONDITION_H

#include "Mutex.h"

#include <boost/noncopyable.hpp>

namespace agilNet
{

class Condition : boost::noncopyable
{
public:
    explicit Condition(Mutex& mutex)
      : mutex(mutex)
    {
        if(pthread_cond_init(&pcond, NULL)<0)
        {

        }
    }

    ~Condition()
    {
        if(pthread_cond_destroy(&pcond)<0)
        {

        }
    }

    void wait()
    {
        if(pthread_cond_wait(&pcond, mutex.getPthreadMutex())<0)
        {

        }
    }
    void notify()
    {
        if(pthread_cond_signal(&pcond))
        {

        }
    }

    void notifyAll()
    {
        if(pthread_cond_broadcast(&pcond))
        {

        }
    }

private:
    Mutex& mutex;
    pthread_cond_t pcond;
};

}
#endif
