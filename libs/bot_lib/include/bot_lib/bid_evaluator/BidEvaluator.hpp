#pragma once
#include <utils/Player.hpp>
#include "../bot_utils/GameState.hpp"
#include "../bot_utils/GlobalGameState.hpp"

namespace bot
{

const int REQUIRED_LEGAL_SAMPLES = 100;

class BidEvaluator
{
    public:
    virtual utils::Bid evalueNextBid(GameState& state, const GlobalGameState& globalState) = 0;
};


} // namespace bot
