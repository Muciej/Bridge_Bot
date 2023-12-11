#pragma once
#include <memory>
#include <vector>
#include <string>
#include <bot_lib/bot_utils/GameState.hpp>
#include <bot_lib/bot_utils/GlobalGameState.hpp>
#include <bot_lib/state_evaluator/Evaluator.hpp>
#include <bot_lib/bot_utils/Move.hpp>
#include <bot_lib/bid_evaluator/BidEvaluator.hpp>
#include <bot_lib/bot_utils/MovesGenerator.hpp>
#include <utils/Card.hpp>
#include <utils/Player.hpp>
#include <commands/CommandCreator.hpp>
#include <connection/Client.hpp>

namespace bot
{

using ClientPtr = std::unique_ptr<connection::Client>;

class Bot
{
    private:
    void init_current_state();
    int evaluateNextMoveDetails(const GameState& state, int depth, int alpha, int beta, bool maximize);

    public:
    const int evaluation_depth = 5;
    GameState current_state;
    GlobalGameState global_game_state;
    ClientPtr client;
    std::unique_ptr<Evaluator> state_evaluator;
    std::unique_ptr<BidEvaluator> bid_evaluator;
    commands::CommandCreator command_creator;
    MoveGenerator move_generator;

    // main functions
    Bot(std::string bot_name, ClientPtr client_ptr);
    void gameloop();

    // bot functions
    utils::Card evaluateNextMove(GameState& state);
    utils::Bid evaluateNextBid(GameState& state);

    // server interaction functions
    void executeSetPosCommand(std::vector<std::string> command_data);
    void executeHandCommand(std::vector<std::string> command_data);
    void executeBidderCommand(std::vector<std::string> command_data);
    void executeBidCommand(std::vector<std::string> command_data);
    void executeBidendCommand(std::vector<std::string> command_data);
    void executePlayCommand(std::vector<std::string> command_data);
    void executeTrickendCommand(std::vector<std::string> command_data);
    void executeGameendCommand(std::vector<std::string> command_data);
    void executeDummyHandCommand(std::vector<std::string> command_data);
};

} // namespace bot
