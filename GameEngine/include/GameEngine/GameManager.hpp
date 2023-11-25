#pragma once
#include <connection/TcpServer.hpp>
#include <utils/Player.hpp>
#include <string>

namespace game
{

class WrongCommandException;
class InvalidActionInCurrentStateException;

enum class GameState
{
    IN_LOBBY,
    BIDDING,
    PLAYING,
};

class GameManager
{
    public:
    GameState state = GameState::IN_LOBBY;
    utils::Player players[4];
    bool connected_players[4] = {false, false, false, false};
    utils::Position now_moving;

    GameManager() = default;
    
    void gameLoop(connection::TcpServer& server);
    void addPlayer(std::vector<std::string>& command_data);
    void playerBid(std::vector<std::string>& command_data);
    void playerMove(std::vector<std::string>& command_data);
    void startBidding();
};

};
