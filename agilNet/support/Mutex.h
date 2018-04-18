#ifndef AGILNET_SUPPORT_MUTEX_H
#define AGILNET_SUPPORT_MUTEX_H


#include <boost/noncopyable.hpp>
#include <pthread.h>
#include <support/Log.h>


namespace agilNet
{

class Mutex : boost::noncopyable
{
public:
    Mutex()
    {
        if(pthread_mutex_init(&mutex, NULL)<0)
        {
            agilNet::log::Log::getSingle()->write(agilNet::log::Log::error,"init mutex error.");
        }
    }

    ~Mutex()
    {
        if(pthread_mutex_destroy(&mutex)<0)
        {
            agilNet::log::Log::getSingle()->write(agilNet::log::Log::error,"destroy mutex error .");
        }
    }

    void lock()
    {
        if(pthread_mutex_lock(&mutex)<0)
        {
            agilNet::log::Log::getSingle()->write(agilNet::log::Log::error,"lock mutex error .");
        }
    }

    void unlock()
    {
        if(pthread_mutex_unlock(&mutex)<0)
        {
            agilNet::log::Log::getSingle()->write(agilNet::log::Log::error,"unlock mutex error .");
        }
    }

    pthread_mutex_t* getPthreadMutex()
    {
      return &mutex;
    }

private:
    pthread_mutex_t mutex;
};

class MutexGuard : boost::noncopyable
{
public:
    explicit MutexGuard(Mutex& mutex)
      : mutex(mutex)
    {
        mutex.lock();
    }

    ~MutexGuard()
    {
        mutex.unlock();
    }

private:
    Mutex& mutex;
};

}


#endif
