#pragma once
#include "../bot_utils/GameState.hpp"
#include "../bot_utils/GlobalGameState.hpp"
#include <utils/Player.hpp>

namespace bot
{

class Evaluator
{
    public:
    virtual int evaluateState(const GameState& state, const GlobalGameState& global_state) = 0;
};

} // namespace bot
