#pragma once
#include "Evaluator.hpp"
#include "../bot_utils/GameState.hpp"

namespace bot
{

const int WON_TRICKS_MULTIPLIER = 40;
const int ALLY_POINT_MULTIPLIER = 1;
const int ENEMY_POINT_MULTIPLIER = -1;

class BaseEvaluator : public Evaluator
{
    public:
    int evaluateState(const GameState& state, const GlobalGameState& global_state);
};

} // namespace bot
