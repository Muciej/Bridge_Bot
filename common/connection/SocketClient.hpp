#pragma once
#include <QueueContainer.hpp>
#include <memory>

class SocketClient
{
    protected:
    std::unique_ptr<MultiThreadCommandContainer> container;

    public:
    SocketClient(MultiThreadCommandContainer* c) : container{std::make_unique<MultiThreadCommandContainer>(c)} {};

};
