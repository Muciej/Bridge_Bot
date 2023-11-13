#pragma once
#include <commands/MultiThreadCommandContainer.hpp>
#include <queue>
#include <string>

class QueueContainer : public MultiThreadCommandContainer
{
    private:
    std::queue<std::string> queue;
    
    public:
    void pushCommand(std::string&& command) override;
    void pushCommand(const std::string& command) override;
    bool popCommand(std::string& c) override;
    bool isEmpty() override;
    std::string debugPrint();
};