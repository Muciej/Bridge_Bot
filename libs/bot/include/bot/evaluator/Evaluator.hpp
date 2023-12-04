#pragma once
#include "../bot_utils/GameState.hpp"

namespace bot
{

class Evaluator
{
    public:
    virtual int evaluate(const GameState& state) = 0;
};  

} // namespace bot
