#pragma once
#include <memory>
#include <bot/bot_utils/GameState.hpp>
#include <bot/evaluator/Evaluator.hpp>
#include <bot/bot_utils/Move.hpp>
#include <utils/Card.hpp>

namespace bot
{

class Bot
{
    private:
    int evaluateNextMoveDetails(const GameState& state, int depth, int alpha, int beta, bool maximize);
    
    public:
    int evaluation_depth = 5;
    std::unique_ptr<Evaluator> evaluator;

    utils::Card evaluateNextMove(const GameState& state);
}; 

} // namespace bot
