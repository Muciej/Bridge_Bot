#pragma once
#include "../bot_utils/GameState.hpp"
#include "../bot_utils/GlobalGameState.hpp"
#include <utils/Player.hpp>

namespace bot
{

class Evaluator
{
    public:
    /// @brief Evaluates given state with respect to global state of the game
    /// @param state - state to evaluate
    /// @param global_state - global game state
    /// @return evaluated value for given state
    virtual int evaluateState(const GameState& state, const GlobalGameState& global_state) = 0;
};

} // namespace bot
