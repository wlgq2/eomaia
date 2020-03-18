/*
Copyright 2019, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2019-2-28

Description: https://github.com/wlgq2/eomaia
*/

#ifndef     LOG_INTERFACE_H
#define     LOG_INTERFACE_H

#include <string>
#include <functional>
#include <atomic>
#include <iostream>

namespace base
{

class LogInterface
{
public:
    virtual ~LogInterface(){}

    virtual void warn(const std::string& data) = 0;
    virtual void error(const std::string& data) = 0;
    virtual void info(const std::string& data) = 0;
    virtual void debug(const std::string& data) = 0;
};

class Log
{
public:
    using OutMessageType = std::function<void(const std::string&)>;
    enum Level{
        Debug = 0,
        Info,
        Warn,
        Error
    };
    static Log* Instance()
    {
        static Log single;
        return &single;
    }
    void registerInterface(LogInterface* handle)
    {
        handle_ = handle;
        funcs_[Debug] = std::bind(&LogInterface::debug, handle_, std::placeholders::_1);
        funcs_[Info] = std::bind(&LogInterface::info, handle_, std::placeholders::_1);
        funcs_[Warn] = std::bind(&LogInterface::warn, handle_, std::placeholders::_1);
        funcs_[Error] = std::bind(&LogInterface::error, handle_, std::placeholders::_1);
    }
    void write(int level,std::string& data)
    {
        if ((handle_) &&(level<= Error) && (level >= Debug))
        {
            funcs_[level](data);
        }
        else
            std::cout<<data;
    }
    void write(int level, std::string&& data)
    {
        if ((handle_) && (level <= Error))
        {
            funcs_[level](data);
        }
        else
            std::cout<<data;
    }
    void warn(const std::string& data)
    {
        if (handle_)
            handle_->warn(data);
        else
            std::cout<<data<<std::endl;
    }
    void warn(const std::string&& data)
    {
        if (handle_)
            handle_->warn(data);
        else
            std::cout<<data<<std::endl;
    }
    void error(const std::string& data)
    {
        if (handle_)
            handle_->error(data);
        else
            std::cerr<<data<<std::endl;
    }
    void error(const std::string&& data)
    {
        if (handle_)
            handle_->error(data);
        else
            std::cerr<<data<<std::endl;
    }
    void info(const std::string& data)
    {
        if (handle_)
            handle_->info(data);
        else
            std::cout<<data<<std::endl;
    }
    void info(const std::string&& data)
    {
        if (handle_)
            handle_->info(data);
        else
            std::cout<<data<<std::endl;
    }
    void debug(const std::string& data)
    {
        if (handle_)
            handle_->debug(data);
        else
            std::cout<<data<<std::endl;
    }
    void debug(const std::string&& data)
    {
        if (handle_)
            handle_->debug(data);
        else
            std::cout<<data<<std::endl;

    }

    static void ToHex(std::string& message,const char* data,unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            char buf[8];
            std::sprintf(buf, " 0x%x ", (unsigned char)data[i]);
            message += buf;
        }
    }

    Log& operator<<(std::string&& str)
    {
        write(currentLevel_,str);
        return *Instance();
    }


    Log& operator<<(std::string& str)
    {
        write(currentLevel_,str);
        return *Instance();
    }

    static Log& OUT(Level level)
    {
        Instance()->currentLevel_ = level;
        return *Instance();
    }
private:
    Log():handle_(nullptr)
    {
    }

    LogInterface* handle_;
    OutMessageType funcs_[Error + 1];

    std::atomic<Level> currentLevel_;
};
}
#endif // !  UV_LOG_INTERFACE_H

