#pragma once
#include <memory>
#include <vector>
#include <string>
#include <bot/bot_utils/GameState.hpp>
#include <bot/bot_utils/GlobalGameState.hpp>
#include <bot/evaluator/Evaluator.hpp>
#include <bot/bot_utils/Move.hpp>
#include <bot/moves_optimizations/MoveOptimizer.hpp>
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
    int evaluation_depth = 5;
    utils::Position now_moving;
    GameState current_state;
    GlobalGameState global_game_state;
    ClientPtr client;
    std::unique_ptr<Evaluator> evaluator;
    std::unique_ptr<MoveOptimizer> move_optimize_chain;
    commands::CommandCreator command_creator;

    // main functions
    Bot(std::string bot_name, ClientPtr client_ptr);
    void gameloop();

    // bot functions
    utils::Card evaluateNextMove(const GameState& state);
    void generateStatesAfterEachMove(const std::vector<Move>& moves);
    std::vector<Move> generateMoves(const GameState& state);
    std::vector<Move> generateLegalMoves(const GameState& state);
    utils::Bid evaluateNextBid(const GameState& state);
    void updateCurrentStateAfterBid();
    void updateStateAfterMove(GameState& state, const utils::Card& played_card, const utils::Position& played_position);
    void resetPoints(utils::Position position);

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
