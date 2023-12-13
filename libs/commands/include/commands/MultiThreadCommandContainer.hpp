#pragma once
#include <mutex>
#include <string>


/// @brief Interface for container supporting multithreaded use
class MultiThreadCommandContainer
{
    public:
    std::mutex mutex;
    virtual void pushCommand(std::string&& command) = 0;
    virtual void pushCommand(const std::string& command) = 0;
    virtual bool popCommand(std::string& c) = 0;
    virtual bool isEmpty() = 0;

    virtual ~MultiThreadCommandContainer() {};
};
