#pragma once
#include <utils/Player.hpp>
#include "../bot_utils/GameState.hpp"
#include "../bot_utils/GlobalGameState.hpp"

namespace bot
{

class BidEvaluator
{
    public:
    virtual utils::Bid evalueNextBid(const GameState& state, const GlobalGameState& globalState) = 0;
};


} // namespace bot
