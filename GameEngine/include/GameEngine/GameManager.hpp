#pragma once
#include <connection/TcpServer.hpp>

namespace Game
{

enum class GameState
{
    BIDDING,
    PLAYING,
};

class GameManager
{
    private:
    GameState state = GameState::BIDDING;

    public:
    GameManager() = default;
    void gameLoop(const connection::TcpServer& server);

};

};
