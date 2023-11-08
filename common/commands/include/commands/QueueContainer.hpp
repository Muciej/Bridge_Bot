#pragma once
#include "commands/MultiThreadCommandContainer.hpp"
#include <queue>
#include <string>
#include <utility>
#include <iostream>

class QueueContainer : public MultiThreadCommandContainer
{
    private:
    std::queue<std::string> queue;
    
    public:
    void pushCommand(std::string&& command) override
    {
        queue.emplace(command);
    }

    void pushCommand(std::string& command) override
    {
        queue.emplace(std::move(command));
    }

    bool popCommand(std::string& c) override
    {
        auto isEmpty = queue.empty();
        if (!isEmpty)
        {
            c = queue.front();
            queue.pop();
        }
        return !isEmpty;
    }

    bool isEmpty() override
    {
        return queue.empty();
    }

    std::string debugPrint()
    {
        std::stringstream ss;
        ss << "Size of queue: " << queue.size()
           << "\t Top most element: " << queue.front() << std::endl;
        return ss.str();
    }
};