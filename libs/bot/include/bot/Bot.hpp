#pragma once
#include <memory>
#include <vector>
#include <string>
#include <bot/bot_utils/GameState.hpp>
#include <bot/evaluator/Evaluator.hpp>
#include <bot/bot_utils/Move.hpp>
#include <bot/moves_optimizations/MoveOptimizer.hpp>
#include <utils/Card.hpp>
#include <connection/TcpClient.hpp>

namespace bot
{

using ClientPtr = std::unique_ptr<connection::TcpClient>;

class Bot
{
    private:
    int evaluateNextMoveDetails(const GameState& state, int depth, int alpha, int beta, bool maximize);
    
    public:
    ClientPtr client;
    std::string name;
    int evaluation_depth = 5;
    std::unique_ptr<Evaluator> evaluator;
    std::unique_ptr<MoveOptimizer> move_optimize_chain;

    Bot(ClientPtr client_ptr, std::string bot_name);
    void gameloop();
    utils::Card evaluateNextMove(const GameState& state);
    std::vector<Move> generateMoves(const GameState& state);
    std::vector<Move> generateLegalMoves(const GameState& state);

    void executeSetPosCommand(std::vector<std::string> command_vector);
    void executeHandCommand(std::vector<std::string> command_vector);
    void executeBidderCommand(std::vector<std::string> command_vector);
    void executeBidCommand(std::vector<std::string> command_vector);
    void executeBidendCommand(std::vector<std::string> command_vector);
    void executePlayCommand(std::vector<std::string> command_vector);
    void executeTrickendCommand(std::vector<std::string> command_vector);
    void executeGameendCommand(std::vector<std::string> command_vector);
    void executeDummyHandCommand(std::vector<std::string> command_vector);
}; 

} // namespace bot
