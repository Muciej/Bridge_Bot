#pragma once
#include <memory>
#include <vector>
#include <string>
#include <bot/bot_utils/GameState.hpp>
#include <bot/evaluator/Evaluator.hpp>
#include <bot/bot_utils/Move.hpp>
#include <bot/moves_optimizations/MoveOptimizer.hpp>
#include <utils/Card.hpp>
#include <utils/Player.hpp>
#include <connection/TcpClient.hpp>

namespace bot
{

using ClientPtr = std::unique_ptr<connection::TcpClient>;

class Bot
{
    private:
    int evaluateNextMoveDetails(const GameState& state, int depth, int alpha, int beta, bool maximize);
    
    public:
    // game params
    std::string name;
    utils::Position position;


    ClientPtr client;
    int evaluation_depth = 5;
    GameState current_state;
    std::unique_ptr<Evaluator> evaluator;
    std::unique_ptr<MoveOptimizer> move_optimize_chain;

    Bot(ClientPtr client_ptr, std::string bot_name);
    void gameloop();
    utils::Card evaluateNextMove(const GameState& state);
    std::vector<Move> generateMoves(const GameState& state);
    std::vector<Move> generateLegalMoves(const GameState& state);
    utils::Bid evaluateNextBid(const GameState& state);

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
