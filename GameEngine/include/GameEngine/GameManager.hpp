#pragma once
#include <utils/Player.hpp>
#include <string>
#include <memory>

#include <connection/Server.hpp>
#include <commands/CommandCreator.hpp>
#include <utils/Bidding.hpp>
#include <utils/Dealer.hpp>

namespace game
{

enum class GameState
{
    IN_LOBBY,
    BIDDING,
    PLAYING,
};

using ServerPtr = std::unique_ptr<connection::Server>;

class GameManager
{
    public:
    ServerPtr server;
    commands::CommandCreator command_creator;
    utils::Bidding bidding;
    utils::Dealer dealer;

    utils::Player players[4];
    bool connected_players[4] = {false, false, false, false};
    utils::Position now_moving;
    bool shouldPrintInfo = false;
    GameState state = GameState::IN_LOBBY;

    GameManager(ServerPtr server_ptr) : server(std::move(server_ptr)) {};
    
    void gameLoop();
    void addPlayer(std::vector<std::string>& command_data);
    void playerBid(std::vector<std::string>& command_data);
    void playerMove(std::vector<std::string>& command_data);
    void startBidding();
    bool isGameFull();
    void infoPrint(const std::string& msg);
    utils::Position getPlayerPosition(std::string name);
};

};
