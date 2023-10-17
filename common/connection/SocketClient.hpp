#pragma once
#include <commands/MultiThreadCommandContainer.hpp>
#include <memory>

class SocketClient
{
    protected:
    std::unique_ptr<MultiThreadCommandContainer> inMsgContainer;
    std::unique_ptr<MultiThreadCommandContainer> outMsgContainer;

    public:
    SocketClient(MultiThreadCommandContainer* in, MultiThreadCommandContainer* out) 
        : inMsgContainer{std::make_unique<>(in)}, outMsgContainer{std::make_unique<>(in)} {};
};
