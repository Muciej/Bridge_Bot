#pragma once
#include "MultiThreadCommandContainer.hpp"
#include <queue>
#include <string>
#include <utility>

class QueueContainer : public MultiThreadCommandContainer
{
    private:
    std::queue<std::string> queue;
    
    public:
    void pushCommand(std::string& command) override
    {
        queue.emplace(std::move(command));
    }

    bool popCommand(std::string& c) override
    {
        if (!queue.empty())
        {
            c = queue.front();
            queue.pop();
        }
        return !queue.empty();
    }
};
