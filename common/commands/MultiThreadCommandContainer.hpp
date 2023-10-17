#pragma once
#include <mutex>

class MultiThreadCommandContainer
{
    public:
    std::mutex mutex;
    virtual void pushCommand(std::string& command) = 0;
    virtual bool popCommand(std::string& c) = 0;

    virtual ~MultiThreadCommandContainer() {};
};
