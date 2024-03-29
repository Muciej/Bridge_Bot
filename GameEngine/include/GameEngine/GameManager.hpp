#pragma once
#include <utils/Player.hpp>
#include <string>
#include <memory>

#include <connection/Server.hpp>
#include <commands/CommandCreator.hpp>
#include <utils/Bidding.hpp>
#include <utils/Dealer.hpp>
#include <utils/Game.hpp>

namespace game
{

using utils::GameState;
using ServerPtr = std::unique_ptr<connection::Server>;

class GameManager
{
    public:
    ServerPtr server;
    commands::CommandCreator command_creator;
    utils::Bidding bidding;
    utils::Dealer dealer;
    utils::Game game;

    utils::Player players[4];
    utils::Position bidder = utils::Position::NORTH;
    bool connected_players[4] = {false, false, false, false};
    bool shouldPrintInfo = false;

    GameManager(ServerPtr server_ptr) : server(std::move(server_ptr)) {};

    void gameLoop();
    void addPlayer(std::vector<std::string>& command_data);
    void playerBid(std::vector<std::string>& command_data);
    void playerMove(std::vector<std::string>& command_data);
    void playerDummyMove(std::vector<std::string>& command_data);
    void startBidding();
    void startGame();
    bool isGameFull();
    void infoPrint(const std::string& msg);
    void generateAndSendDeck();
    bool isCommandLegal(int desired_cmd_length, GameState required_state, const utils::Position& player_position, std::vector<std::string>& command_data);
    void revealDummysCards();
    void updateNowMoving();
    void updateBidder();
    void endGame();
    void checkTrickEnd();
};

};
