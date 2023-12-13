#pragma once
#include <commands/MultiThreadCommandContainer.hpp>
#include <queue>
#include <string>

/// @brief Queue that encapsulates std::queue
/// to enable support for multithreaded use
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