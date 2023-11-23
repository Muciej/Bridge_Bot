#pragma once
#include <connection/TcpServer.hpp>
#include <GameEngine/Player.hpp>
#include <string>

namespace Game
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
    Player players[4];
    bool connected_players[4] = {false, false, false, false};

    GameManager() = default;
    
    void gameLoop(connection::TcpServer& server);
    std::string parseCommand(std::string command, std::vector<std::string>& command_data);
    void addPlayer(std::vector<std::string>& command_data);
    void playerBid(std::vector<std::string>& command_data);
    void playerMove(std::vector<std::string>& command_data);
};

};
